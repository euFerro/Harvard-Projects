# Generated by Django 4.2.1 on 2023-09-06 11:30

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('network', '0009_post_comment_count'),
    ]

    operations = [
        migrations.AlterField(
            model_name='user',
            name='profile_picture',
            field=models.ImageField(default='profile/default.jpeg', upload_to='profile'),
        ),
    ]
