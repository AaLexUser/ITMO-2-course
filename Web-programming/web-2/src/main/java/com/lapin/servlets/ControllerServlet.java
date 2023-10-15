package com.lapin.servlets;

import com.lapin.bean.HttpError;
import com.lapin.bean.ResultCollectionManager;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "controller", value = "/controller")
public class ControllerServlet extends HttpServlet {

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        if(request.getParameter("x") != null && request.getParameter("y") != null
            && request.getParameter("r") != null){
            getServletContext().getRequestDispatcher("/check").forward(request, response);
        }
        else if(request.getParameter("clean") != null){
            ResultCollectionManager hitCollection = (ResultCollectionManager) request.getSession().getAttribute("hitCollection");
            if (hitCollection == null) hitCollection = new ResultCollectionManager();
            hitCollection.clear();
            request.getSession().setAttribute("hitCollection", hitCollection);
            getServletContext().getRequestDispatcher("/index.jsp").forward(request,response);
        }
        else{
            new HttpError(404, "Page not found").setError(request);
        }
    }
}