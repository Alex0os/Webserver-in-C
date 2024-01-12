# Welcome to my first project: Webserver with C.

## Description

This repository will be about creating a functional webserver with C. The final idea is that this webserver has all the necessary 
components to be used for building (at least) simple applications.

## Checklist

- [x] Create the routing for valid URIs defines by the developer
   - [x] Create a hash table that stores valid URIs and their corresponding resources
   - [x] Create a function that allows to create a valid linking between an URI and a resource

- [ ] Create an HTML parser that scan all the resources for the HTML resources linked to valid routes
    - [ ] Use the route of the resource in the HTML file as a key and the value of that key should be the content of the file

- [ ] Creating a simple middleware for the server
