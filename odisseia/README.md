# ODISSEIA

## Overview
ODISSEIA is an information system for health institutions with data warehouse functionality developed using the PostgreSQL DBMS.

The program enables **health institutions to register prescriptions** using a PostgreSQL database, as well as providing a **Flask web interface** for better UX and **data mining operations** for analytics.


## Running ODISSEIA
To run ODISSEIA, you should use the builtin functionality of PostgreSQL to create and populate the database from the SQL files.

First, make sure you install PostgreSQL by using the following commands:

```console
sudo apt update && sudo apt upgrade
sudo apt install postgresql
```

Then, start the PostgreSQL server:

```console
sudo service postgresql start
sudo su -l postgres
dropdb foo
createdb foo
psql foo
CREATE USER foo WITH SUPERUSER LOGIN PASSWORD 'bar';
```

You are now ready to load the SQL files. You can do so with the following:

```console
\i <path_to_file>
```

For instance:

```console
\i schema.sql
```

You should do this following the order `schema.sql` -> `RI.sql` -> `star_schema.sql` -> `populate.sql` -> `etl.sql` (first schema creation, then populating the tables). Afterwards, you can run the provided example queries, `queries.sql` and `olap.sql`.

The Flask application uses **CGI**, so deploying the webpage might be a bit more tedious. See [Flask - CGI](https://flask.palletsprojects.com/en/2.0.x/deploying/cgi/) for details. You should also change the DBMS configs in `app.cgi` to match the ones you used previously and generate a new secret key.

A more thorough overview of the general architecure can be found in *assignment1.pdf* and *assignment2.pdf* (in portuguese) and *report1_1.pdf*, *report1_2.pdf* and *report2.pdf* (also in portuguese).


## Academic details
This project was developed for BD (Bases de Dados) - a third year programming class about DBMSs and other database-related concepts.

It was done with the help of @Mafalda92512 (https://github.com/Mafalda92512).

The final grade was **19.40/20.00** in the first part (basic database functionality and webpage) and **14.60/20.00** in the second (data warehouse functionality and analytics).
