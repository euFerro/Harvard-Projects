from django.contrib.auth.models import AbstractUser
from django.db import models
from django.forms import ModelForm
from django import forms

class User(AbstractUser):
    profile_picture = models.ImageField(upload_to="profile", blank=False, default="profile/default.jpeg")
    followers_count = models.IntegerField(default=0)
    following_count = models.IntegerField(default=0)
    def __str__(self) -> str:
        full_name = f'{self.first_name} {self.last_name}' if self.first_name or self.last_name else None
        return f"{self.username} ({full_name})"

class Follow(models.Model):
    user = models.ForeignKey(
        User,
        on_delete=models.CASCADE,
        related_name='my_follow'
    )
    follow = models.ForeignKey(
        User,
        on_delete=models.CASCADE
    )
    created_at = models.DateTimeField(auto_now_add=True)
    def __str__(self) -> str:
        return f'Follow({self.user.username}, {self.follow.username})'


class FollowForm(ModelForm):
    class Meta:
        model = Follow
        fields = [
            "user",
            "follow"
        ]

class FollowForm(forms.Form):
    user = forms.IntegerField(required=True)
    follow = forms.IntegerField(required=True)


class Post(models.Model):
    user = models.ForeignKey(
        User,
        on_delete=models.CASCADE,
        related_name='posts'
    )
    text = models.CharField(max_length=500)
    img = models.ImageField(upload_to="post", blank=True, null=True)
    likes = models.IntegerField(default=0)
    comment_count = models.IntegerField(default=0)
    created_at = models.DateTimeField(auto_now_add=True)
    def __str__(self) -> str:
        return f'Post({self.pk}, {self.text})'


class PostForm(ModelForm):
    class Meta:
        model = Post
        fields = [
            "user",
            "text",
            "img"
        ]

class PostForm(forms.Form):
    user = forms.IntegerField(required=True)
    text = forms.CharField(max_length=500, required=True)
    img = forms.ImageField(allow_empty_file=True, required=False)


class CommentEntry(models.Model):
    post = models.ForeignKey(
        Post,
        on_delete=models.CASCADE,
        related_name="comments"
    )
    comment = models.ForeignKey(
        Post,
        on_delete=models.DO_NOTHING
    )


class LikeEntry(models.Model):
    user = models.ForeignKey(
        User,
        on_delete=models.CASCADE,
        related_name='liked_posts'
    )
    liked_post = models.ForeignKey(
        Post,
        on_delete=models.DO_NOTHING,
        related_name='like_entries'
    )
    created_at = models.DateTimeField(auto_now_add=True)
    def __str__(self) -> str:
        return f'LikeEntry({self.user.username}, {self.liked_post.pk})'


