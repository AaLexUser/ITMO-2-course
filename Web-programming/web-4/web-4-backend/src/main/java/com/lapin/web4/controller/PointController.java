package com.lapin.web4.controller;

import com.lapin.web4.DTO.PointDTO;
import com.lapin.web4.DTO.PointResponse;
import com.lapin.web4.repository.PointRepository;
import com.lapin.web4.utility.Converter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.security.Principal;
import java.util.Collections;
import java.util.List;

@RestController
@RequestMapping("/api/v1")
public class PointController {
    @Autowired
    private PointRepository pointRepository;
    @Autowired
    private Converter converter;

    @PostMapping("/add-point")
    public void addPoint(
            @RequestBody PointDTO pointDTO,
            Principal principal
    ) {
        pointDTO.setUsername(principal.getName());
        pointRepository.save(converter.PointDTOToPoint(pointDTO));
    }
    @GetMapping("/get-points")
    public ResponseEntity<List<PointResponse>> getPoints() {
        return ResponseEntity.ok(pointRepository.findAll().stream().sorted(Collections.reverseOrder()).map(PointResponse::new).toList());
    }
    @PutMapping("/update/{id}")
    public void updatePoint(
            @PathVariable("id") Long id,
            @RequestBody PointDTO pointDTO,
            Principal principal
    ) {
        pointRepository.findById(id).ifPresent(point -> {
            pointDTO.setUsername(principal.getName());
            pointRepository.save(converter.PointDTOToPoint(pointDTO, point));
        });
    }
    @DeleteMapping("/delete/{id}")
    public void deletePoint(
            @PathVariable("id") Long id
    ) {
        pointRepository.deleteById(id);
    }
}
