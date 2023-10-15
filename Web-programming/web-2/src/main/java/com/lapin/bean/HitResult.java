package com.lapin.bean;

import lombok.*;

import java.util.HashMap;
import java.util.Map;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class HitResult {
    Coordinates coordinates;
    private String currentTime;
    private double executionTime;
    private boolean hit;


    private Map<String, String> getMap() {
        Map<String, String> fields = new HashMap<>();
        fields.put("x", String.valueOf(coordinates.getX()));
        fields.put("y", String.valueOf(coordinates.getY()));
        fields.put("r", String.valueOf(coordinates.getR()));
        fields.put("currentTime", String.valueOf(currentTime));
        fields.put("executionTime", String.valueOf(executionTime));
        fields.put("result", String.valueOf(hit));
        return fields;
    }
}
