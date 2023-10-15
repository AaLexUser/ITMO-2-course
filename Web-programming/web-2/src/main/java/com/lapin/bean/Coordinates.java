package com.lapin.bean;

import lombok.AllArgsConstructor;
import lombok.Setter;

import java.io.Serializable;

@AllArgsConstructor
@Setter
public class Coordinates implements Serializable {
    private double x;
    private double y;
    private double r;

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double getR() {
        return r;
    }
}
