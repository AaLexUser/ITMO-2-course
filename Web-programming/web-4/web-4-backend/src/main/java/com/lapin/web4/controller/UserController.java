package com.lapin.web4.controller;

import com.lapin.web4.DTO.PointDTO;
import com.lapin.web4.exception.UserNotFoundException;
import com.lapin.web4.model.AvatarRequest;
import com.lapin.web4.model.AvatarResponse;
import com.lapin.web4.model.User;
import com.lapin.web4.repository.PointRepository;
import com.lapin.web4.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.security.Principal;

@RestController
@RequestMapping("/api/v1")
public class UserController {
    @Autowired
    private UserRepository userRepository;
    @PostMapping("/set-avatar")
    public void setAvatar(
            @RequestBody AvatarRequest avatar,
            Principal principal
    ) {
        userRepository.findByUsername(principal.getName()).ifPresent(user ->{
            user.setAvatar(avatar.getUrl());
            userRepository.save(user);
        });
    }
    @GetMapping("/get-avatar")
    public ResponseEntity<AvatarResponse> getAvatar(
            Principal principal
    ) {
        User user = userRepository.findByUsername(principal.getName()).orElseThrow(()-> new UserNotFoundException(principal.getName()));
        return ResponseEntity.ok(new AvatarResponse(user.getAvatar()));
    }
    @DeleteMapping("/delete-user")
    public void deleteUser( Principal principal) {
        User user = userRepository.findByUsername((principal.getName())).orElseThrow(()-> new UserNotFoundException(principal.getName()));
        userRepository.deleteById(user.getId());
    }
}
