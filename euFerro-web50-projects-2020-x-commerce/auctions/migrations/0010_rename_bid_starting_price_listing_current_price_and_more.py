# Generated by Django 4.2.1 on 2023-06-10 04:30

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('auctions', '0009_alter_user_profile_picture'),
    ]

    operations = [
        migrations.RenameField(
            model_name='listing',
            old_name='bid_starting_price',
            new_name='current_price',
        ),
        migrations.RenameField(
            model_name='listing',
            old_name='current_bid_price',
            new_name='starting_price',
        ),
    ]
