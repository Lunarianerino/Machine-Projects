<%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 14/04/2023
  Time: 5:23 pm
  To change this template use File | Settings | File Templates.
--%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="java.sql.*, java.util.*, hoadb.*" %>
<%@ page import="com.example.hoadb.AssetActivity" %>
<%@ page import="com.example.hoadb.Officer" %>
<%@ page import="com.example.hoadb.Ornum" %>



<html>
<head>
    <link rel="stylesheet" href="style.css">
    <meta http-equiv="Content-Type" content="text/html;  =UTF-8">
    <title>Asset Activity Registration Form</title>

</head>
    <body>
        <jsp:useBean id="activityBean" class="com.example.hoadb.AssetActivity" scope="session" />
        <%
            Officer o = new Officer();
            o.loadAssets();
            Ornum or = new Ornum();
            or.loadORS();
        %>

        <h1>Asset Activity Registration Form</h1>
        <h2>Enter a date to determine which assets are available:</h2>
        <form name = "addactivity" action="addactivity.jsp" method = "POST">
            Activity Date: <input type="date" name = "assetdate" id = "assetdate" required> <br><br>
            <h2>Transaction Details</h2>
            Approved By Officer ID:
            <select name="officer" id = "officer" required>
                <%
                    for (int i = 0; i < o.officers.size(); i++) {
                        Officer e = new Officer();
                        e = o.officers.get(i);
                %>
                <option value = "<%=i%>"> <%=e.ho_id%> - <%=e.position%></option>
                <% } %>
            </select> <br><br>
            Official Receipt Number:
            <select name = "ornum" id = "ornum" required>
                <%
                    for(int i = 0; i< or.ornums.size(); i++) {
                        Ornum g = new Ornum();
                        g = or.ornums.get(i);

                %>
                <option value = "<%=g.ornum%>"> <%=g.ornum%></option>
                <% }%>
            </select><br><br>
            <input type="submit" value="Submit" name="addactivity" />
        </form>
    </body>
</html>
