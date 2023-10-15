package com.lapin.web4.DTO;

import com.lapin.web4.utility.Checker;
import jakarta.validation.constraints.NotNull;
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class PointDTO {
    private Long id;
    private String username;
    @NotNull
    private String x;
    @NotNull
    private String y;
    @NotNull
    private String r;

    private String time;

    private String executionTime;

    private boolean hitResult;


}
