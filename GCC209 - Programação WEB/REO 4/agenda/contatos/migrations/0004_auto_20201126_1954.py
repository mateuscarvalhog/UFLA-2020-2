# Generated by Django 3.1.3 on 2020-11-26 19:54

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('contatos', '0003_auto_20201126_1952'),
    ]

    operations = [
        migrations.AlterField(
            model_name='pessoa',
            name='cep',
            field=models.CharField(max_length=9),
        ),
        migrations.AlterField(
            model_name='pessoa',
            name='cidade',
            field=models.CharField(max_length=50),
        ),
        migrations.AlterField(
            model_name='pessoa',
            name='estado',
            field=models.CharField(max_length=2),
        ),
        migrations.AlterField(
            model_name='pessoa',
            name='logradouro',
            field=models.CharField(max_length=100),
        ),
        migrations.AlterField(
            model_name='pessoa',
            name='numero',
            field=models.CharField(max_length=10),
        ),
    ]
