<%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 16/04/2023
  Time: 6:08 pm
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@page import="java.sql.*, java.util.*, hoadb.*" %>
<%@ page import="com.example.hoadb.Officer" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <title>Homeowner's Association Database Login Page</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
<h1>Homeowner's Association Database Login Page</h1>
<jsp:useBean id="officerBean" class="com.example.hoadb.Officer" scope="session" />
<%

    String name = request.getParameter("name");
    int hoid = Integer.parseInt(request.getParameter("hoid"));

    officerBean.loadAssets();

    Officer test = new Officer();
    boolean isOfficer = false;
    for (Officer officer : officerBean.officers) {
        if (officer.ho_id == hoid) {
            test = officer;
            isOfficer = true;
            break; // exit the loop once a matching officer is found
        }
    }
    if (isOfficer) {
        if (test.position.equals("President")){

%>
        Welcome,President <%=name%>!<br><br>
        ID Number: <%=hoid%>
        <form name ="mainmenu" action="activity_delete.jsp" method = "POST">
            <input type ='hidden' name="position" id="position" value =<%=test.position%>>
            <input type="submit" value="Submit" name="login" />
        </form>
    <%
        } else { %>
        You are not a president!

    <% }
    } else {%>
        You are not an officer!

    <%}%>
Click <a href="index.jsp">here to go back to the main menu.</a><br>
</body>
</html>
