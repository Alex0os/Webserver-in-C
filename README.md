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

- [x] Create a process that takes the URI that the request is asking for to give a propper response
    - [x] Create a function that takes the resource route in the system and then returns an HTTP header based on its file extention
    - [x] Debug the problem that makes the terminal hang on in execution mode when the compiled output is executed
    - [x] See if after the modification of the "response_buffer" buffer function, some functions in "utils.c" are still needed

- [x] Modify the process to obtain the content of the resource that is being asked by the HTTP request
    - [x] Simplify the process to wrap the "Content-Type" sub-type value in the response header
    - [x] Modify the process that gives the value of the "Content-Type" to define its main type before creating the header
    - [ ] Refactoring the process of getting the resource content to cover a wider range of exceptions and making it more readable



- [ ] Creating a simple middleware for the server
    - [ ] Create a 400 related response states
