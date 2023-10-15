package com.lapin.web4.exception;

public class UserNotFoundException extends RuntimeException{
    public UserNotFoundException(String username) {
        super("Could not find the user with username " + username);
    }
}
