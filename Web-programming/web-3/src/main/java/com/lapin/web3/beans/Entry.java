package com.lapin.web3.beans;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import javax.annotation.ManagedBean;
import javax.enterprise.context.RequestScoped;
import javax.enterprise.context.SessionScoped;
import javax.persistence.*;
import java.io.Serializable;

@Setter
@Getter
@NoArgsConstructor
@AllArgsConstructor
@ManagedBean("entry")
@RequestScoped
public class Entry implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "jpaSequence")
    @SequenceGenerator(name = "jpaSequence", sequenceName = "JPA_SEQUENCE", allocationSize = 1)
    @Column(name = "id", nullable = false)
    private int id;

    private Double x;
    private Double y;
    private Double r;
    private String hitResult;

    @Override
    public String toString() {
        return "Entry{" +
                "x=" + x +
                ", y=" + y +
                ", r=" + r +
                ", hitResult=" + hitResult +
                '}';
    }

    @Override
    public int hashCode() {
        return x.hashCode() + y.hashCode() +
                r.hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj instanceof Entry) {
            Entry entryObj = (Entry) obj;
            return x.equals(entryObj.getX()) &&
                    y.equals(entryObj.getY()) &&
                    r.equals(entryObj.getR());
        }
        return false;
    }
}
