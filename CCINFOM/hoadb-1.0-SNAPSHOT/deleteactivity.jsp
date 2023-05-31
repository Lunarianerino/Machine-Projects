<%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 15/04/2023
  Time: 12:42 am
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <title>Asset Activity Deletion</title>
</head>
<body>
    <h1>Asset Activity Deletion</h1>
    <jsp:useBean id="activityBean" class="com.example.hoadb.AssetActivity" scope="session" />
    <%
        String activityid = request.getParameter("activityid");
        System.out.println(activityid);

        if (!activityid.equals("none"))
        {
            String[] activity_pk = activityid.split("-",2);
            System.out.println(activity_pk[0]);
            System.out.println(activity_pk[1]);
            int asset_id = Integer.parseInt(activity_pk[0]);
            activityBean.updateActivity("SET status = \"D\" WHERE asset_id = " + asset_id + " AND activity_date = \"" + activity_pk[1] + "\"");%>
            Deleted Activity Successfully.
    <%} else {
    %>
            No activity was selected.
    <% ;}%>
    Click <a href="index.jsp">here to go back to main menu</a><br>
</body>
</html>
