package com.lapin.web4.utility;

public class Checker {
    private final Double x;
    private final Double y;
    private final Double r;
    public Checker(Double x, Double y, Double r) {
        this.x = x;
        this.y = y;
        this.r = r;
    }
    public boolean checkHit() {
        return checkTriangle() || checkRectangle() || checkCircle();
    }
    private boolean checkTriangle() {
        return x >=0 && y <=0 && (-y + x <=(double) r);
    }

    private boolean checkRectangle() {
        return x <= 0 && y <= 0 && Math.abs(x) <= r/2 && Math.abs(y) <= (double) r;
    }

    private boolean checkCircle() {
        return x >= 0 && y >= 0 && x * x + y * y <= (double) r * r /4;
    }
}
