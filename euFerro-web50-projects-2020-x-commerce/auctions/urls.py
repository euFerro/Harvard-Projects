from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("login", views.login_view, name="login"),
    path("logout", views.logout_view, name="logout"),
    path("register", views.register, name="register"),
    path("listings/<str:listing_id>", views.listings, name="listings"),
    path("close/<str:listing_id>", views.close, name='close'),
    path("remove_comment/<str:listing_id>", views.remove_comment, name="remove_comment"),
    path("categories", views.categories, name="categories"),
    path("categories/<str:category>", views.category, name="category"),
    path("watchlist", views.watchlist, name="watchlist"),
    path("createlisting", views.createlisting, name="createlisting"),
]
