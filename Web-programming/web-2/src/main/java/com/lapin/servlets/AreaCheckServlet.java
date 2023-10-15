package com.lapin.servlets;

import com.lapin.bean.Coordinates;
import com.lapin.bean.HitResult;
import com.lapin.bean.HttpError;
import com.lapin.bean.ResultCollectionManager;
import com.lapin.utils.CoordinatesValidation;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.time.OffsetDateTime;
import java.time.ZoneOffset;
import java.time.format.DateTimeFormatter;

@WebServlet(name = "areaCheck", value = "/check")
public class AreaCheckServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        long startTime = System.nanoTime();
        String rawX = request.getParameter("x");
        String rawY = request.getParameter("y");
        String rawR = request.getParameter("r");
        Coordinates coordinates = null;
        try {
            coordinates = CoordinatesValidation.getCoordinates(rawX,rawY,rawR);
        } catch (Exception e) {
            HttpError error = new HttpError(404, "Illegal number format");
            request.getSession().setAttribute("error",error);
        }

        OffsetDateTime currentTimeUTC = OffsetDateTime.now(ZoneOffset.UTC);
        try {
            currentTimeUTC = currentTimeUTC.minusMinutes(Long.parseLong(request.getParameter("timezone")));
        } catch (Exception e) {
            new HttpError(404, "Timezone is NULL").setError(request);
            return;
        }
        String currentTime = currentTimeUTC.format(DateTimeFormatter.ofPattern("HH:mm:ss"));
        HitResult hitResult = new HitResult();
        hitResult.setCoordinates(coordinates);
        hitResult.setCurrentTime(currentTime);
        BigDecimal executionTime = BigDecimal.valueOf((double) (System.nanoTime() - startTime) / 1000000);
        BigDecimal zeroOne = new BigDecimal("0.1");
        BigDecimal zeroTwo = new BigDecimal("0.2");
        for(int i = 1; i < 10; i++){
            if(executionTime.setScale(i, RoundingMode.HALF_UP).compareTo(BigDecimal.ZERO) != 0 &&
                    executionTime.setScale(i, RoundingMode.HALF_UP).compareTo(zeroOne) != 0 &&
                        executionTime.setScale(i, RoundingMode.HALF_UP).compareTo(zeroTwo) != 0)
            {
                executionTime = executionTime.setScale(i, RoundingMode.HALF_UP);
                break;
            }
        }

        hitResult.setExecutionTime(executionTime.doubleValue());
        hitResult.setHit(isHit(coordinates));

        ResultCollectionManager hitCollection = (ResultCollectionManager) request.getSession().getAttribute("hitCollection");
        if(hitCollection == null) hitCollection = new ResultCollectionManager();
        hitCollection.add(hitResult);
        request.setAttribute("hitCollection", hitCollection);
    }
    private boolean isHit(Coordinates coordinates) {
        return isCircleHit(coordinates) || isRectangleHit(coordinates) || isTriangleHit(coordinates);
    }
    private boolean isCircleHit(Coordinates coordinates){
        boolean isFirstQuadrant = coordinates.getX() >= 0 && coordinates.getY() >= 0;
        return isFirstQuadrant && (Math.pow(coordinates.getX(),2) + Math.pow(coordinates.getY(),2) <= Math.pow(coordinates.getR(),2));
    }
    private boolean isTriangleHit(Coordinates coordinates) {
        boolean isThirdQuadrant = coordinates.getX() <= 0 && coordinates.getY() <= 0;
        return isThirdQuadrant && (coordinates.getY() >= (-2) * coordinates.getX() - coordinates.getR());
    }
    private boolean isRectangleHit(Coordinates coordinates) {
        boolean isFourthQuadrant = coordinates.getX() >= 0 && coordinates.getY() <= 0;
        return isFourthQuadrant && (coordinates.getX() <= coordinates.getR()) && (coordinates.getY() >= -coordinates.getR());
    }

}
