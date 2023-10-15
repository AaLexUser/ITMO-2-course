package com.lapin.web4.model;

import jakarta.persistence.*;
import jakarta.validation.constraints.Max;
import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotNull;
import lombok.*;

import java.math.BigDecimal;
import java.time.OffsetDateTime;

@Getter
@Setter
@Builder
@Entity
@AllArgsConstructor
@NoArgsConstructor(force = true)
public class Point implements Comparable<Point> {
    @Id
    @GeneratedValue
    private Long id;
    @NotNull
    @Min(-5)
    @Max(3)
    private Double x;
    @NotNull
    @Min(-3)
    @Max(3)
    private Double y;
    @NotNull
    @Min(-5)
    @Max(3)
    private Double r;
    @NotNull
    private Boolean hitResult;
    @NotNull
    private OffsetDateTime time;
    @NotNull
    private BigDecimal executionTime;

    @NotNull
    @ManyToOne(cascade = CascadeType.MERGE)
    @JoinColumn(name = "user_id")
    private User user;

    @Override
    public int compareTo(Point o) {
        return this.time.compareTo(o.time);
    }
}
