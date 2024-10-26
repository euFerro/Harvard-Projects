from django.contrib.auth.models import AbstractUser
from django.db import models
from django.core.validators import MinValueValidator
from django.forms import ModelForm
from django import forms

class User(AbstractUser):
    profile_picture = models.ImageField(upload_to="imgs/profile/", blank=False, default="imgs/profile/default.jpeg")


class Listing(models.Model):
    DEFAULT_CATEGORY = 'No Selection'
    FASHION = 'Clothing and Fashion'
    TOYS_AND_GAMES = 'Toys and Games'
    ELECTRONICS = 'Electronics'
    HOME_AND_KITCHEN = 'Home and Kitchen'
    FOOD = 'Groceries and Food'
    HEALTH = 'Health and Beauty'
    BOOK = 'Books and Stationery'
    SPORTS = 'Sports and Fitness'
    AUTOMOTIVE = 'Automotive'
    DECOR = 'Furniture and Decor'
    PET = 'Pet Supplies'
    TOOLS = 'Tools and Hardware'
    JEWELRY = 'Jewelry and Accessories'
    BABY = 'Baby and Maternity'
    MUSIC = 'Music and Instruments'
    ENTERTAINMENT = 'Movies and Entertainment'
    OFFICE = 'Office Supplies'
    TRAVEL = 'Travel and Luggage'
    GARDEN = 'Garden and Outdoor'
    ARTS_AND_CRAFTS = 'Arts and Crafts'
    CATEGORIES_CHOICES = [
        (DEFAULT_CATEGORY, 'No Selection'),
        (FASHION, 'Clothing and Fashion'),
        (TOYS_AND_GAMES, 'Toys and Games'),
        (ELECTRONICS, 'Electronics'),
        (HOME_AND_KITCHEN, 'Home and Kitchen'),
        (FOOD, 'Groceries and Food'),
        (HEALTH, 'Health and Beauty'),
        (BOOK, 'Books and Stationery'),
        (SPORTS, 'Sports and Fitness'),
        (AUTOMOTIVE, 'Automotive'),
        (DECOR, 'Furniture and Decor'),
        (PET, 'Pet Supplies'),
        (TOOLS, 'Tools and Hardware'),
        (JEWELRY, 'Jewelry and Accessories'),
        (BABY, 'Baby and Maternity'),
        (MUSIC, 'Music and Instruments'),
        (ENTERTAINMENT, 'Movies and Entertainment'),
        (OFFICE, 'Office Supplies'),
        (TRAVEL, 'Travel and Luggage'),
        (GARDEN, 'Garden and Outdoor'),
        (ARTS_AND_CRAFTS, 'Arts and Crafts'),
    ]
    # attributes
    title = models.CharField(max_length=64)
    description = models.TextField(max_length=250)
    starting_price = models.FloatField(default=0)
    current_price = models.FloatField(default=0)
    img = models.ImageField(upload_to="imgs/", null=True, blank=True)
    category = models.CharField(
        max_length=30,
        choices=CATEGORIES_CHOICES, # --- Categories ---
        default=DEFAULT_CATEGORY,
    )
    created_at = models.DateTimeField(auto_now_add=True)
    last_updated = models.DateTimeField(auto_now=True)
    owner = models.ForeignKey(
        User,
        on_delete=models.CASCADE,
        related_name="listings"
    )
    closed = models.BooleanField(default=False, blank=True)

    def __str__(self) -> str:
        return f"{self.title}"
    
class ListingForm(ModelForm):
    class Meta:
        model = Listing
        fields = [
            "title",
            "description",
            "starting_price",
            "current_price",
            "img",
            "category",
            "owner",
        ]

class ListingForm(forms.Form):
    title = forms.CharField(max_length=64)
    description = forms.CharField(max_length=250)
    starting_price = forms.FloatField(min_value=1)
    current_price = forms.FloatField(min_value=1)
    img = forms.ImageField(allow_empty_file=True) # optional
    category = forms.CharField(
        widget=forms.Select(choices=Listing.CATEGORIES_CHOICES)
    )
    owner = forms.CharField()


class Bid(models.Model):
    listing = models.ForeignKey(
        Listing, on_delete=models.CASCADE, related_name="bids"
    )
    user = models.ForeignKey(
        User, on_delete=models.CASCADE, related_name="bids"
    )
    value = models.FloatField(default=0, validators=[MinValueValidator(0)])
    created_at = models.DateTimeField(auto_now_add=True)

class BidForm(ModelForm):
    class Meta:
        model = Bid
        fields = [
            "listing",
            "user",
            "value"
        ]

class BidForm(forms.Form):
    listing = forms.CharField()
    user = forms.CharField()
    value = forms.FloatField(max_value=1000000000000)


class Comment(models.Model):
    user = models.ForeignKey(
        User, on_delete=models.CASCADE, related_name="comments"
    )
    listing = models.ForeignKey(
        Listing, on_delete=models.CASCADE, related_name="comments"
    )
    text = models.TextField(max_length=250, default='')
    created_at = models.DateTimeField(auto_now_add=True)


class WatchlistEntry(models.Model):
    user =  models.ForeignKey(
        User, on_delete=models.CASCADE, related_name="watchlisted"
    )
    listing = models.ForeignKey(
        Listing, on_delete=models.CASCADE, related_name="watchlists"
    )
    created_at = models.DateTimeField(auto_now_add=True)