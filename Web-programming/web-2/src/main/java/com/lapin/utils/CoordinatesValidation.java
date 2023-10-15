package com.lapin.utils;

import com.lapin.bean.Coordinates;

public class CoordinatesValidation {
    private static final double MIN_X = -5, MAX_X = 3;
    private static final double MIN_Y = -5, MAX_Y = 3;
    private static final double MIN_R = 1, MAX_R = 4;

    public static Coordinates getCoordinates(String rawX, String rawY, String rawR) throws Exception {
        double x = validate(rawX,MIN_X,MAX_X);
        double y = validate(rawY,MIN_Y,MAX_Y);
        double r = validate(rawR,MIN_R,MAX_R);
        return new Coordinates(x,y,r);
    }
    private static double validate(String coord, double min, double max) throws Exception {
        coord = coord.trim();
        double dCoord = Double.parseDouble(coord);
        if(dCoord < min || dCoord > max){
            throw new Exception();
        }
        return dCoord;
    }
}
