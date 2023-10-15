package com.lapin.web4.DTO;

import com.lapin.web4.model.Point;
import jakarta.validation.constraints.NotNull;
import lombok.*;

import java.math.BigDecimal;
import java.time.OffsetDateTime;
@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@Builder
public class PointResponse {

    private Long id;
    private String username;
    @NotNull
    private Double x;
    @NotNull
    private Double y;
    @NotNull
    private Double r;

    private String time;

    private BigDecimal executionTime;

    private Boolean hitResult;

    public PointResponse(Point point){
        this.id = point.getId();
        this.username = point.getUser().getUsername();
        this.x = point.getX();
        this.y = point.getY();
        this.r = point.getR();
        this.time = point.getTime().toString();
        this.executionTime = point.getExecutionTime();
        this.hitResult = point.getHitResult();
    }
}
