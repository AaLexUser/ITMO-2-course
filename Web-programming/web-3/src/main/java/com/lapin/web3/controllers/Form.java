package com.lapin.web3.controllers;

import com.lapin.web3.beans.Entries;
import com.lapin.web3.beans.Entry;
import com.lapin.web3.utility.Checker;
import lombok.Getter;
import lombok.Setter;
import org.primefaces.model.SortMeta;

import javax.annotation.ManagedBean;
import javax.annotation.PostConstruct;
import javax.enterprise.context.SessionScoped;
import javax.faces.application.FacesMessage;
import javax.faces.context.FacesContext;
import javax.inject.Inject;
import javax.inject.Named;
import javax.validation.constraints.Max;
import javax.validation.constraints.Min;
import javax.validation.constraints.NotNull;
import java.io.IOException;
import java.io.Serializable;
import java.util.List;

@Named
@SessionScoped
@Setter
@Getter
public class Form implements Serializable {
    private Double x;
    private Double y;
    private Boolean[] r;
    private Double[] rValues;
    private String hitResult;
    @Inject
    private Entries entries;

    @PostConstruct
    public void init(){
        r = new Boolean[5];
        rValues = new Double[]{1.0, 1.5, 2.0, 2.5, 3.0};
    }



    public void submit() throws IOException {
        for (int i = 0; i < r.length; i++) {
            if (r[i] != null && r[i]) {
                Entry entry = new Entry();
                entry.setX(x);
                entry.setY(y);
                entry.setR(rValues[i]);
                entry.setHitResult(new Checker(x, y, rValues[i]).checkHit());
                entries.addEntry(entry);
            }
        }
        x = null;
        y = null;
        FacesContext.getCurrentInstance().getExternalContext().redirect("home.xhtml");
    }

    /**
     * Clears all entries in the table
     * @throws IOException
     */
    public void clear() throws IOException {
        entries.clearEntries();
        FacesContext.getCurrentInstance().getExternalContext().redirect("home.xhtml");
    }

    public void addMessage(FacesMessage.Severity severity, String summary, String detail) {
        FacesContext.getCurrentInstance().
                addMessage(null, new FacesMessage(severity, summary, detail));
    }
    public void showInfo(String summary, String detail) {
        addMessage(FacesMessage.SEVERITY_INFO, summary, detail);
    }

    @Override
    public String toString() {
        return "Form {" +
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

}
