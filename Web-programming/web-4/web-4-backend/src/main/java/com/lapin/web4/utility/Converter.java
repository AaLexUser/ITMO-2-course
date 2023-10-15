package com.lapin.web4.utility;

import com.lapin.web4.DTO.PointDTO;
import com.lapin.web4.exception.UserNotFoundException;
import com.lapin.web4.model.Point;
import com.lapin.web4.model.User;
import com.lapin.web4.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.time.OffsetDateTime;
import java.time.ZoneOffset;
@Service
public class Converter {
    @Autowired
    private UserRepository userRepository;
    public Point PointDTOToPoint(PointDTO pointDTO, Point point){
        long startTime = System.nanoTime();
        point.setX(StringToDouble(pointDTO.getX()));
        point.setY(StringToDouble(pointDTO.getY()));
        point.setR(StringToDouble(pointDTO.getR()));
        point.setTime(OffsetDateTime.now(ZoneOffset.UTC));
        point.setHitResult(new Checker(point.getX(), point.getY(), point.getR()).checkHit());
        String username = pointDTO.getUsername();
        User user = userRepository.findByUsername(username).orElseThrow(()-> new UserNotFoundException(username));
        point.setUser(user);
        point.setExecutionTime(getCorrectTime((double)(System.nanoTime() - startTime) / 1000000));
        return point;
    }

    public Point PointDTOToPoint(PointDTO pointDTO) {
        return PointDTOToPoint(pointDTO, new Point());
    }

    public PointDTO PointToPointDTO(Point point) {
        PointDTO pointDTO = new PointDTO();
        pointDTO.setId(point.getId());
        pointDTO.setX(point.getX().toString());
        pointDTO.setY(point.getY().toString());
        pointDTO.setR(point.getR().toString());
        pointDTO.setHitResult(point.getHitResult());
        pointDTO.setTime(point.getTime().toString());
        pointDTO.setExecutionTime(point.getExecutionTime().toString());
        pointDTO.setUsername(point.getUser().getUsername());
        return pointDTO;
    }
    private static BigDecimal getCorrectTime(double time){
        int maxNumCount = 10;
        BigDecimal correctTime = BigDecimal.valueOf(time);
        BigDecimal zeroOne = new BigDecimal("0.1");
        BigDecimal zeroTwo = new BigDecimal("0.2");
        for(int i = 1; i < maxNumCount; i++){
            if(correctTime.setScale(i, RoundingMode.HALF_UP).compareTo(BigDecimal.ZERO) != 0 &&
                    correctTime.setScale(i, RoundingMode.HALF_UP).compareTo(zeroOne) != 0 &&
                    correctTime.setScale(i, RoundingMode.HALF_UP).compareTo(zeroTwo) != 0)
            {
                correctTime = correctTime.setScale(i, RoundingMode.HALF_UP);
                break;
            }
        }
        return correctTime;
    }
    private static Double StringToDouble(String str) {
        if(str == null || str.isEmpty()) {
            return null;
        }
        return Double.parseDouble(str.replace(",", "."));
    }
    private static Long StringToLong(String str) {
        if(str == null || str.isEmpty()) {
            return null;
        }
        return Long.parseLong(str);
    }
}
