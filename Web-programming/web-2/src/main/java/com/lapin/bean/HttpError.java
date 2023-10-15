package com.lapin.bean;

import lombok.AllArgsConstructor;
import lombok.Setter;

import javax.servlet.http.HttpServletRequest;
import java.io.Serializable;

@AllArgsConstructor
@Setter
public class HttpError implements Serializable {
    private int statusCode;
    private String errorMessage;

    public void setError(HttpServletRequest request){
        request.getSession().setAttribute("error",this);
    }

    public int getStatusCode() {
        return statusCode;
    }

    public String getErrorMessage() {
        return errorMessage;
    }
}
