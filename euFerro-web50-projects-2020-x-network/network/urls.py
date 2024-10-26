
from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("login", views.login_view, name="login"),
    path("logout", views.logout_view, name="logout"),
    path("register", views.register, name="register"),

    # API routes
    path('home', views.home, name="home"),
    path("post", views.post, name="post_simple"),
    path("profile", views.profile, name="profile"),
    path("follow", views.follow, name="follow"),
    path("unfollow/<int:follow_id>", views.unfollow, name="unfollow"),
    path("posts", views.posts, name="posts"),
    path("explore", views.explore, name="explore"),
    path("like", views.like, name="like"),
    path("unlike/<int:post_id>", views.unlike, name="unlike"),
    path("editpost/<int:post_id>", views.editpost, name="editpost")
]
