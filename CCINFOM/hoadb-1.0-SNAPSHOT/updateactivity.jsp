<%@ page import="com.example.hoadb.AssetActivity" %>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="java.sql.*, java.util.*, hoadb.*" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Updated Activity</title>
</head>
<body>
<h1>Updated Activity</h1>
<jsp:useBean id="activityBean" class="com.example.hoadb.AssetActivity" scope="session" />

<%
    activityBean.failed = false;
    activityBean.loadActivities();
    activityBean = activityBean.assetActivities.get(Integer.parseInt(request.getParameter("index")));
    activityBean.tent_start = request.getParameter("tentative-start");
    activityBean.tent_end = request.getParameter("tentative-end");
    activityBean.act_start = request.getParameter("activity-start");
    activityBean.act_end = request.getParameter("activity-end");
    activityBean.status = request.getParameter("status");
    activityBean.updateActivity();
    if (!activityBean.failed){
%>
    Listing contents of the cart so far<br>
    Asset Name: <%=activityBean.getAssetName()%> (<%=activityBean.asset_id%>)<br>
    Activity Date: <%=activityBean.activity_date%><br>
    Activity Description: <%=activityBean.activity_description%><br>
    Tentative Start: <%=activityBean.tent_start%><br>
    Tentative End: <%=activityBean.tent_end%><br>
    Actual Start: <%=activityBean.act_start%><br>
    Actual End: <%=activityBean.act_end%><br>
<% } else { %>
    <h3 style="color:red"> Error Updating Activity </h3>
    Reason: <%=activityBean.errorMessage%> <br><br>

<% }%>
click <a href="index.jsp">here to go back to main menu</a><br>
</body>
</html>
