# Welcome to my first project: Webserver with C.

## Description

This repository will be about creating a functional webserver with C. The final idea is that this webserver has all the necessary 
components to be used for building (at least) simple applications.

## Checklist

- [x] Create the routing for valid URIs defines by the developer
   - [x] Create a hash table that stores valid URIs and their corresponding resources
   - [x] Create a function that allows to create a valid linking between an URI and a resource

- [x] Create a process that get al the file content for every file inside the "src/" folder that is not an HTML file
    - [x] Create a process that get the content of all the folders inside "src/" folder
    - [x] List al the files inside the previously mentioned folders
    - [x] Create a process that can take all the content of these files
    - [x] Create a hash table where each item has the relative route of the file inside the "src/" folder as the key
    - [x] Make the value of that key the content of the file

- [ ] Create a process that takes the URI that the request is asking for to give a propper response
    - [x] Create a function that takes the resource route in the system and then returns an HTTP header based on its file extention
    - [x] Debug the problem that makes the terminal hang on in execution mode when the compiled output is executed


- [ ] Creating a simple middleware for the server
