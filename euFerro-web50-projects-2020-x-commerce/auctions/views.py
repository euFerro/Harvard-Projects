from django.contrib.auth import authenticate, login, logout
from django.db import IntegrityError
from django.http import HttpResponseRedirect
from django.shortcuts import render, redirect
from django.urls import reverse
from django.contrib.auth.decorators import login_required

from .models import User, Listing, WatchlistEntry, Comment, ListingForm, Bid, BidForm


def index(request):
    context = {
        "title": 'Active Listings',
        "listings": Listing.objects.all()
    }
    return render(request, "auctions/index.html", context)


def login_view(request):
    if request.method == "POST":

        # Attempt to sign user in
        username = request.POST["username"]
        password = request.POST["password"]
        user = authenticate(request, username=username, password=password)

        # Check if authentication successful
        if user is not None:
            login(request, user)
            return HttpResponseRedirect(reverse("index"))
        else:
            return render(request, "auctions/login.html", {
                "message": "Invalid username and/or password."
            })
    else:
        return render(request, "auctions/login.html")

@login_required()
def logout_view(request):
    logout(request)
    return HttpResponseRedirect(reverse("index"))


def register(request):
    if request.method == "POST":
        username = request.POST["username"]
        email = request.POST["email"]

        # Ensure password matches confirmation
        password = request.POST["password"]
        confirmation = request.POST["confirmation"]
        if password != confirmation:
            return render(request, "auctions/register.html", {
                "message": "Passwords must match."
            })

        # Attempt to create new user
        try:
            user = User.objects.create_user(username, email, password)
            user.save()
        except IntegrityError:
            return render(request, "auctions/register.html", {
                "message": "Username already taken."
            })
        login(request, user)
        return HttpResponseRedirect(reverse("index"))
    else:
        return render(request, "auctions/register.html")

class InvalidValueException(Exception):
    pass

def listings(request, listing_id):
    if request.method == 'POST':

        if request.POST["action"] == "COMMENT":
            # Add a comment to a listing
            try:
                user = User.objects.get(id=request.POST["user_id"])
                listing = Listing.objects.get(id=listing_id)
                comment_text = request.POST["comment_text"]
                # Save new comment
                new_comment = Comment(user=user, listing=listing, text=comment_text)
                new_comment.save()
            except Exception as e:
                return HttpResponseRedirect(f"{listing_id}?error={e.__repr__()}")
            # Comment added successfully
            return HttpResponseRedirect(f"{listing_id}?success=Comment added successfully")
        
        elif request.POST["action"] == "BID":
            data = {
                "user": request.POST["user_id"],
                "value": request.POST["value"],
                "listing": listing_id,
            }
            form = BidForm(data=data)
            if form.is_valid():
                try:
                    # Create new biding and update lsiting current value
                    user = User.objects.get(id=form.cleaned_data["user"])
                    listing = Listing.objects.get(id=listing_id)
                    value = form.cleaned_data["value"]
                    if value <= listing.current_price:
                        raise InvalidValueException(f"The value must be greater than {value}")
                    new_bid = Bid(
                        listing = listing,
                        user = user,
                        value = value
                    )
                    listing.current_price = value
                    new_bid.save()
                    listing.save()
                    if None == WatchlistEntry.objects.get(listing=listing):
                        watchlist = WatchlistEntry(user=user, listing=listing)
                        watchlist.save()
                    return HttpResponseRedirect(f'{listing_id}?bid_success=Bid Added Successfully')
                except Exception as e:
                    return HttpResponseRedirect(f'{listing_id}?bid_error={e}')
            else:
                return HttpResponseRedirect(f'{listing_id}?bid_error=This field is required')
    else:
        # GET a listing from the database
        try:
            listing = Listing.objects.get(id=listing_id)
            watchlisted = WatchlistEntry.objects.filter(listing=listing)
            comments = Comment.objects.filter(listing=listing).all()
            context = {
                "listing": listing,
                "watchlisted": watchlisted,
                "comments": comments,
                "error": request.GET.get('error'),
                "success": request.GET.get('success'),
                "min_price": listing.current_price + 1,
                "bids": enumerate(Bid.objects.filter(listing=listing).order_by('-value')[:3]),
                "bid_success": request.GET.get('bid_success'),
                "bid_error": request.GET.get('bid_error'),
                "closed_success": request.GET.get('closed_success'),
                "closed_invalid": request.GET.get('closed_invalid'),
            }
            return render(request, "auctions/listing.html", context)
        except Exception:
            return render(request, "auctions/not_found.html")

@login_required()
def close(request, listing_id):
    if request.method == 'POST':
        try:
            listing = Listing.objects.get(id=listing_id)
            listing.closed = True
            listing.save()
            return HttpResponseRedirect(f'/listings/{listing_id}?closed_success=You sold the auction sucessfully')
        except Exception:
            return HttpResponseRedirect(f'/listings/{listing_id}?closed_invalid=You sold the auction sucessfully')
    else:
        return HttpResponseRedirect(f'/listings/{listing_id}?closed_invalid=Invalid method GET for selling the auction')

@login_required()
def remove_comment(request, listing_id):
    if request.method == "POST":
        comment_id = request.POST["comment_id"]
        comment = Comment.objects.get(id=comment_id)
        comment.delete()
        return redirect(f'/listings/{listing_id}')
    else:
        return render(request, "auctions/not_found.html")

def categories(request):
    if request.method == 'GET':
        context = {
            "categories": map(lambda choice: choice[0], Listing.CATEGORIES_CHOICES)
        }
        return render(request, "auctions/categories.html", context)
    else:
        return render(request, "auctions/not_found.html")

def category(request, category):
    if request.method == 'GET':
        context = {
        "title": category,
        "listings": Listing.objects.filter(category=category) 
        }
        return render(request, "auctions/index.html", context)
    else:
        return render(request, "auctions/not_found.html")

@login_required()
def watchlist(request):
    current_user = request.user

    if request.method == 'POST':
        operation = request.POST["operation"]
        listing_id = request.POST["id"]
        listing = Listing.objects.get(id=listing_id)
        if operation == "add":
            entry = WatchlistEntry(user=current_user, listing=listing)
            entry.save()
            return redirect(f'/listings/{listing_id}')
        else:
            entry = WatchlistEntry.objects.get(listing=listing)
            entry.delete()
            return redirect(f'/listings/{listing_id}')
    else:
        items = WatchlistEntry.objects.filter(user=current_user).all()
        listings = map(lambda item: item.listing, items)
        context = {
            "title": 'My Watchlist',
            "listings": listings
        }
        return render(request, "auctions/index.html", context)

@login_required()
def createlisting(request):
    if request.method == "POST":
        data = {
            "title": request.POST["title"],
            "description": request.POST["description"],
            "starting_price": request.POST["starting_price"],
            "current_price": request.POST["starting_price"], # current_price is the same as the starting_price when created
            "category": request.POST["category"],
            "owner": request.POST["owner"],
        }
        form = ListingForm(data=data, files=request.FILES)
        if form.is_valid():
            try:
                user_owner = User.objects.get(id=form.cleaned_data["owner"])
                new_listing = Listing(
                    title = form.cleaned_data["title"],
                    description = form.cleaned_data["description"],
                    starting_price = form.cleaned_data["starting_price"],
                    current_price = form.cleaned_data["current_price"],
                    img = form.cleaned_data["img"],
                    category = form.cleaned_data["category"],
                    owner = user_owner
                )
                new_listing.save()
                # Add to user's watchlist
                WatchlistEntry(user=user_owner, listing=new_listing).save()
                return redirect(f"watchlist")
            except Exception:
                context = {
                    "form": form,
                    "user_id_error": "Are you trying to hack me dude??",
                }
                return render(request, "auctions/create_listing.html", context)
        else:
            context = {
                "form": form,
            }
            return render(request, "auctions/create_listing.html", context)
    else:
        form = ListingForm()
        context = {
            "form": form,
        }
        return render(request, "auctions/create_listing.html", context)