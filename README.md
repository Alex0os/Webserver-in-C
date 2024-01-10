# Welcome to my first project: Webserver with C.

## Description

This repository will be about creating a functional webserver with C. The final idea is that this webserver has all the necessary 
components to be used for building (at least) simple applications.

## Checklist

- [ ] Create the routing for valid URIs defines by the developer
   - [ ] Create a hash table that stores valid URIs and their corresponding resources
      - [ ] Create a function that allows to create a valid linking between an URI and a resource
      - [ ] Create a procedure where it is stated if the URI has an extention or not
      - [ ] If it has an extention, then use it to search the folder where the resource is located
      - [ ] If it doesn't, then search for the resource related to the URI
   - [ ] Create the necessary piece of middleware to inform the client that the URI is invalid
- [ ] Creating a simple middleware for the server
