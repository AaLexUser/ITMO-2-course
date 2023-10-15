<%@ page import="com.lapin.bean.HitResult" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<table id="table">
    <jsp:useBean id="hitCollection" class="com.lapin.bean.ResultCollectionManager" scope="session"/>
    <thead>
    <th>X</th>
    <th>Y</th>
    <th>R</th>
    <th>HIT RESULT</th>
    <th>CURRENT TIME</th>
    <th>EXECUTION TIME, SEC</th>
    </thead>
    <tbody>
    <%
        if (hitCollection != null) {
            for (HitResult result : hitCollection.getResultList()) {
    %>

    <tr>
        <td class="x"><%=result.getCoordinates().getX()%>
        </td>
        <td class="y"><%=result.getCoordinates().getY()%>
        </td>
        <td class="r"><%=result.getCoordinates().getR()%>
        </td>
        <td class="hit" style='color:<%=(result.isHit() ? "#0A8059" : "#ff0404")%>'>
            <%= result.isHit() ? "hit" : "miss" %>
        </td>
        <td><%=result.getCurrentTime()%>
        </td>
        <td><%=result.getExecutionTime()%>
        </td>
    </tr>
    <%
            }
        }
    %>
    </tbody>
</table>
