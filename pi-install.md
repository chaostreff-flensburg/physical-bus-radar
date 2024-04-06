
# As ubuntu/pi user
## Install needed Packages

	sudo apt install postgresql postgis udo git git-lfs python3 python3-pip python3-venv

### ubuntu only
	sudo apt install python3.8-venv

## Install python dependencies

	python3 -m venv venv
	source venv/bin/activate
	pip3 install -r requirements.txt
	mkdir static

# Create a new user and database

	sudo su postgres

# All as user postgres
	createuser busradar -P --interactive
## Create a new database

	psql
	CREATE DATABASE busradar;

## Enable postgis extension

	psql busradar
	CREATE EXTENSION postgis;

## import data

	psql busradar < busradar-schema.sql 