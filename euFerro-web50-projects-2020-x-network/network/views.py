from django.contrib.auth import authenticate, login, logout
from django.db import IntegrityError
from django.http import HttpResponse, JsonResponse, HttpResponseRedirect
from django.shortcuts import render, redirect
from django.urls import reverse
from django.views.decorators.csrf import csrf_exempt
from django.contrib.auth.decorators import login_required
from django.core import serializers
from django.http.multipartparser import MultiPartParser
import json
import os

from .models import User, Post, Follow, PostForm, FollowForm, LikeEntry


def home(request):
    return render(request, "index.html")

@csrf_exempt
def login_view(request):
    if request.method == "POST":

        # Attempt to sign user in
        try:
            username = request.POST["username"]
            password = request.POST["password"]
            user = authenticate(request, username=username, password=password)
        except Exception:
            user = authenticate(request=request)
        try:
            user_obj = User.objects.get(pk=user.pk)
            following_username_list = [follow.follow.username for follow in Follow.objects.filter(user=user_obj)]
            liked_posts_id_list = [like_entry.liked_post.pk for like_entry in LikeEntry.objects.filter(user=user_obj)]
            user_json = {
                "user_id": user_obj.pk,
                "username": user_obj.username,
                "first_name": user_obj.first_name,
                "last_name": user_obj.last_name,
                "profile_picture_url": user_obj.profile_picture.url,
                "followers_count": user_obj.followers_count,
                "following_count": user_obj.following_count,
                "following_username_list": following_username_list,
                "liked_posts": liked_posts_id_list
            }
            login(request, user)
            return JsonResponse({
                "user": json.dumps(user_json)
            }, status=200)
        
        except Exception:
            return JsonResponse({
                "error": "Invalid username and/or password."
            }, status=404)
    else:
        return redirect(reverse('home'))


def logout_view(request):
    logout(request)
    return HttpResponseRedirect(reverse("home"))

def register(request):
    if request.method == "POST":
        username = request.POST["username"]
        email = request.POST["email"]

        print(username, email)

        first_name = request.POST["first_name"]
        last_name = request.POST["last_name"]

        # Ensure password matches confirmation
        password = request.POST["password"]
        confirmation = request.POST["confirmation"]
        if password != confirmation:
            return JsonResponse({
                "error_password": "Passwords must match."
            }, status=403)

        # Attempt to create new user
        try:
            user = User.objects.create_user(username, email, password)
            user.first_name = first_name
            user.last_name = last_name
            user.save()
        except IntegrityError:
            return JsonResponse({
                "error_username": "Username already taken."
            }, status=403)
        login(request, user)
        user_obj = User.objects.get(pk=user.pk)
        following_username_list = [follow.follow.username for follow in Follow.objects.filter(user=user_obj)]
        liked_posts_id_list = [like_entry.liked_post.pk for like_entry in LikeEntry.objects.filter(user=user_obj)]
        user_json = {
                "user_id": user.pk,
                "username": user.username,
                "first_name": user.first_name,
                "last_name": user.last_name,
                "profile_picture_url": user.profile_picture.url,
                "followers_count": user.followers_count,
                "following_count": user.following_count,
                "following_username_list": following_username_list,
                "liked_posts": liked_posts_id_list
            }
        return JsonResponse({
            "user": json.dumps(user_json)
        }, status=200)
    else:
        return render(request, "index.html")


# API views -------------------------------------------- 

@login_required
def post(request):
    if request.method == "POST":
        data = {
            "user": request.POST["user"],
            "text": request.POST["text"],
        }
        # Bind form
        form = PostForm(data=data, files=request.FILES)

        if form.is_valid():
            user_id = form.cleaned_data["user"]
            text = form.cleaned_data["text"]

            user = User.objects.get(id=user_id)

            # Test if input is valid
            if len(text) == 0:
                return JsonResponse({
                    "error": "No text was provided"
                }, status=403)
            # Create post
            new_post = Post(
                user = user,
                text = text,
                img = form.cleaned_data["img"]
                )
            new_post.save()
            # Get and Return Post data
            text = new_post.text
            user_id = new_post.user.pk
            username = new_post.user.username
            profile_picture_url = new_post.user.profile_picture.url
            try:
                image_url = new_post.img.url
            except Exception:
                image_url = ''
            likes = new_post.likes
            year = new_post.created_at.year
            month = new_post.created_at.month
            day = new_post.created_at.day
            hour = new_post.created_at.hour
            minute = new_post.created_at.minute
            second = new_post.created_at.second
            return JsonResponse({
                "ok": "Post sent successufully",
                "post": {
                    "key": new_post.pk,
                    "text": text,
                    "user_id": user_id,
                    "username": username,
                    "profile_picture_url": profile_picture_url,
                    "image_url": image_url,
                    "likes": likes,
                    "comment_count": new_post.comment_count,
                    "created_at": {
                        "year": year,
                        "month": month,
                        "day": day,
                        "hour": hour,
                        "minute": minute,
                        "second": second
                    }
                }
            }, status=200)
    
        else:
            return JsonResponse({
                "error": "Invalid data was provided"
            }, status=403)
    else:
       return JsonResponse({
            "error": "The request method for '/post' endpoint is supposed to be POST"
        }, status=405)
        

def profile(request):
    if request.method == 'GET':
        username = request.GET.get("username")
        if username ==  None:
            user = request.user
        else:
            try:
                user = User.objects.get(username=username)
            except Exception:
                return JsonResponse({
                    "error": "User not found."
                }, status=404)
        
        following_username_list = [follow.follow.username for follow in Follow.objects.filter(user=user)]
        liked_posts_id_list = [like_entry.liked_post.pk for like_entry in LikeEntry.objects.filter(user=user)]
        user_json = {
            "user_id": user.pk,
            "username": user.username,
            "first_name": user.first_name,
            "last_name": user.last_name,
            "profile_picture_url": user.profile_picture.url,
            "followers_count": user.followers_count,
            "following_count": user.following_count,
            "following_username_list": following_username_list,
            "liked_posts": liked_posts_id_list
        }
        return JsonResponse({
            "user": json.dumps(user_json)
        })
    else:
        return JsonResponse({
            "error": "The request method for '/profile' endpoint is supposed to be GET"
        }, status=405)
    
@login_required
def follow(request):
    if request.method == 'POST':
        # Loads request data
        data = {
            "user": request.POST["user_id"],
            "follow" : request.POST["follow_id"]
        }
        follow_form = FollowForm(data=data)

        if follow_form.is_valid():
            try:
                # Get users
                user = User.objects.get(id=follow_form.cleaned_data["user"])
                follow = User.objects.get(id=follow_form.cleaned_data["follow"])

            except Exception:
                if not follow:
                    return JsonResponse({
                        "error": "Trying to follow invalid user"
                    }, status=403)
                else: 
                    return JsonResponse({
                        "error": "Invalid user trying to follow"
                    }, status=403)
                
            # Create entry
            new_follow = Follow(user=user, follow=follow)
            new_follow.save()
            user.following_count += 1
            user.save()
            follow.followers_count += 1
            follow.save()
            return JsonResponse({
                "ok": f"User({user.username}) is now following User({follow.username})"
            }, status=200)
        else:
            return JsonResponse({
                "error": "Invalid data, wrong format was provided"
            }, status=403)
    else:
        return JsonResponse({
            "error": "The request method for '/follow' endpoint is supposed to be POST"
        }, status=405)

@login_required
def unfollow(request, follow_id):
    if request.method == 'DELETE':
        try:
            # Get Follow Entry to delete
            follow_user = User.objects.get(id=follow_id)
            logged_user = request.user
            follow_objs = Follow.objects.filter(user=logged_user, follow=follow_user)
            for follow_obj in follow_objs:
                follow_obj.delete()
            logged_user.following_count -= 1
            logged_user.save()
            follow_user.followers_count -= 1
            follow_user.save()

            return JsonResponse({
                "ok": f"User({follow_obj.user.username})unfollowed User({follow_obj.follow.username}) successfully"
            }, status=200)

        except Exception as e:
            if not follow_obj:
                return JsonResponse({
                    "error": f"Cannot unfollow a user that you have never followed"
                }, status=403)
            else:
                return JsonResponse({
                    "error": f"{e.__repr__()}"
                }, status=500)
    else:
        return JsonResponse({
            "error": "The request method for '/unfollow' endpoint is supposed to be DELETE"
        }, status=405)

@login_required
def like(request):
    if request.method == 'POST':
        user = request.user
        post_id = request.POST.get("post_id", None)
        print(post_id)
        if post_id == None:
            return JsonResponse({
                "error": "No post_id was provided to create a like entry."
            }, status=400)
        try:
            post_obj = Post.objects.get(id=post_id)
        except Exception:
            return JsonResponse({
                "error": "The post you are trying to like doesn't exist anymore."
            }, status=404)
        try:
            new_like = LikeEntry(
                user=user,
                liked_post=post_obj
            )
            new_like.save()
            post_obj.likes += 1
            post_obj.save()
            return JsonResponse({
                "ok": f"Successfully liked post {post_obj.pk}"
            })
        except Exception as e:
            return JsonResponse({
                "error": f"Server Error! - Could not save like entry"
            }, status=500)
    else:
        return JsonResponse({
            "error": f"Request is formatted incorrectly, Like API endpoint only accepts POST requests not {request.method}."
        }, status=400)
    
@login_required
def unlike(request, post_id):
    if request.method == 'DELETE':
        user = request.user
        if post_id:
            try:
                post = Post.objects.get(id=post_id)
            except Exception:
                return JsonResponse({
                    "error": "The post you're trying to delete doesn't exist anymore."
                }, status=400)
        else:
            return JsonResponse({
                "error": "No post_id was provided"
            }, status=400)
        try:
            like_entry = LikeEntry.objects.get(
                user=user,
                liked_post=post
            )
            like_entry.delete()
            post.likes -= 1
            post.save()
            return JsonResponse({
                "ok": f"Successfully unliked post {post.pk}"
            })
        except Exception:
            return JsonResponse({
                "error": "The post you're trying to delete doens't exist anymore."
            }, status=400)
    else:
        return JsonResponse({
            "error": f"Resquest is formatted incorrectly, Unlike API endpoint only accepts DELETE requests not {request.method}."
        }, status=400)


def posts(request):
    if request.method == 'GET':

        start = int(request.GET.get("start") or 0)
        end = int(request.GET.get("end") or 10)
        # If wrong interval provided
        if int(start) >= int(end) or int(start) < 0 or int(end) < 0:
            start = 0
            end = 10
        print(start, end)

        posts = [] 
        posts_json = []

        if request.GET.get("q") == 'single-post':
            post_id = request.GET.get('post_id')
            posts = [Post.objects.get(id=post_id)]
            print(f'SINGLE POST, Post id = {post_id}')

        if request.GET.get("q") == 'following-posts':
            print('GET FOLLOWING POSTS')
            if request.user.is_authenticated:
                user = User.objects.get(username=request.user.username)
                print(f'Logged User = {user}')
                follows = Follow.objects.filter(user=user)
                following = [follow.follow for follow in follows]
                print(f'Following: {following}')
                for user in following:
                    user_posts = Post.objects.filter(user=user).order_by('-created_at')[start:end]
                    for post in user_posts:
                        posts.append(post)
                sorted(posts, key=lambda post: post.created_at)

        if request.GET.get("q") == 'user-posts':
            print("GET USER POSTS")
            username = request.GET.get('username')
            try:
                user = User.objects.get(username=username)
            except Exception:
                return JsonResponse({
                    "error": "User not found 404"
                }, status=404)
            posts = Post.objects.prefetch_related().filter(user=user).order_by("-created_at")

        if request.GET.get('q') == 'all-posts':
            posts = Post.objects.prefetch_related().all().order_by("-created_at")[start:end]
        
        if request.GET.get('q') == 'liked-posts':
            if request.user.is_authenticated:
                posts = [like_entry.liked_post for like_entry in LikeEntry.objects.filter(user=request.user).order_by("-created_at")[start:end]]
            else:
                return JsonResponse({
                    "error": "(!) Error - User is not logged in."
                })

        for post in posts:
                text = post.text
                user_id = post.user.pk
                username = post.user.username
                profile_picture_url = post.user.profile_picture.url
                try:
                    image_url = post.img.url
                except Exception:
                    image_url = ''
                likes = post.likes
                year = post.created_at.year
                month = post.created_at.month
                day = post.created_at.day
                hour = post.created_at.hour
                minute = post.created_at.minute
                second = post.created_at.second
                posts_json.append({
                    "key": post.pk,
                    "text": text,
                    "user_id": user_id,
                    "username": username,
                    "profile_picture_url": profile_picture_url,
                    "image_url": image_url,
                    "likes": likes,
                    "comment_count": post.comment_count,
                    "created_at": {
                        "year": year,
                        "month": month,
                        "day": day,
                        "hour": hour,
                        "minute": minute,
                        "second": second
                    }
                })

        json_response = json.dumps(posts_json)
        # print(json_response)
        return JsonResponse(json_response, safe=False)
    
    else:
        return JsonResponse({
            "error": "The Request is Not Formated as The API Requeires: (This Endpoint only Supports GET Requests !)"
        }, status=403)

@login_required
def editpost(request, post_id):
    if request.method == 'PUT':
        put_data = MultiPartParser(request.META, request, request.upload_handlers).parse() # it will return a tuple object
        put = put_data[0] # it will give you the QueryDict object with your form data.
        data = {
            "user": put["user"],
            "text": put["text"]
        }
        print(put)
        # Bind the form
        form = PostForm(data=data, files=put_data[1])
        if form.is_valid():
            text = form.cleaned_data["text"]
            img = form.cleaned_data["img"]
            print(img)
            try:
                post = Post.objects.get(id=post_id)
            except Exception:
                return JsonResponse({
                    "error": f"Error 404 - Couldn't find the post with id {post_id}."
                }, status=404)
            if len(put) == 2:
                post.img = img
            post.text = text
            post.save()
            return JsonResponse({
                "ok": "Post was saved"
            }, status=200)
        else:
            return JsonResponse({
                "error": "Format Error - Check teh format of the data provided."
            }, status=400)

    else:
        return JsonResponse({
            "error": f"Endpoint Error - API endpoint '/editpost' only accepts PUT requests."
        }, status=400)

def explore(request):
    return render(request, "network/explore.html")

def index(request):
    return render(request, "index.html")
    
