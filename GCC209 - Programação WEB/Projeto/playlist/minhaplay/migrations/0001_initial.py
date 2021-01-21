# Generated by Django 3.1.3 on 2020-12-04 18:09

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Faixa',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('nome', models.CharField(max_length=100)),
                ('artista', models.CharField(max_length=100)),
                ('url', models.URLField()),
            ],
            options={
                'verbose_name_plural': 'Faixas',
            },
        ),
    ]
