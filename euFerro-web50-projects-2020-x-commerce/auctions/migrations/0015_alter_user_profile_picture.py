# Generated by Django 4.2.1 on 2023-06-10 20:22

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('auctions', '0014_alter_user_profile_picture'),
    ]

    operations = [
        migrations.AlterField(
            model_name='user',
            name='profile_picture',
            field=models.ImageField(default='imgs/profile/default.jpeg', upload_to='imgs/profile/'),
        ),
    ]
