# Generated by Django 4.2.1 on 2023-07-21 18:16

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('network', '0005_alter_follow_user'),
    ]

    operations = [
        migrations.AddField(
            model_name='post',
            name='associated_post',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, related_name='comments', to='network.post'),
        ),
        migrations.AddField(
            model_name='post',
            name='is_comment',
            field=models.BooleanField(default=False),
        ),
        migrations.DeleteModel(
            name='Comment',
        ),
    ]