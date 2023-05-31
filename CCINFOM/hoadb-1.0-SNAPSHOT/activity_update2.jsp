<%@ page import="com.example.hoadb.AssetActivity" %><%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 14/04/2023
  Time: 2:17 pm
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <meta http-equiv="Content-Type" content="text/html;  =UTF-8">
    <title>Update Asset Form</title>
</head>
<body>
    <h1>Update Activity Form</h1>
    <jsp:useBean id="activityBean" class="com.example.hoadb.AssetActivity" scope="session" />



<form name = "updateAsset" action="updateactivity.jsp" method = "POST">
    <%
        activityBean.loadActivities();
        int index = Integer.parseInt(request.getParameter("activityindex"));
        activityBean = activityBean.assetActivities.get(index);
    %>
    Asset Name: <%=activityBean.getAssetName()%> (<%=activityBean.asset_id%>)<br><br>
    Activity Description: <%=activityBean.activity_description%> <br><br>
    Activity Date: <%=activityBean.activity_date%> <br><br>
    Cost: <%=activityBean.cost%><br><br>

    Tentative Start:
        <input type="date" id = "tentative-start" name = "tentative-start"><br><br>
    Tentative End:
        <input type="date" id = "tentative-end" name = "tentative-end"><br><br>
    Actual Start:
        <input type="date" id = "activity-start" name = "activity-start"><br><br>
    Actual End:
        <input type="date" id = "activity-end" name = "activity-end"><br><br>
    Status:
        <select name="status" id = "status">
            <option value = "S">Scheduled</option>
            <option value = "O">Ongoing</option>
            <option value = "C">Completed</option>
        </select> <br><br>

        <input type='hidden' name='index' id = 'index' value=<%=index%> />
        <input type="submit" value="Submit" name="updateAsset" />
</form>


</body>
</html>
