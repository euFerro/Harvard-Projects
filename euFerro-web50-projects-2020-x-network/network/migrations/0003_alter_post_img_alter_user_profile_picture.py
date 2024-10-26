# Generated by Django 4.2.1 on 2023-07-15 20:28

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('network', '0002_user_followers_count_user_following_count_and_more'),
    ]

    operations = [
        migrations.AlterField(
            model_name='post',
            name='img',
            field=models.ImageField(blank=True, null=True, upload_to='post'),
        ),
        migrations.AlterField(
            model_name='user',
            name='profile_picture',
            field=models.ImageField(default='default.jpeg', upload_to='profile'),
        ),
    ]