<%@ page import="com.example.hoadb.AssetActivity" %><%--
  Created by IntelliJ IDEA.
  User: Luis
  Date: 14/04/2023
  Time: 5:23 pm
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <meta http-equiv="Content-Type" content="text/html;  =UTF-8">
    <title>Update Activity Form</title>
</head>
<body>
    <h1>Update Activity Form</h1>
    <jsp:useBean id="activityBean" class="com.example.hoadb.AssetActivity" scope="session" />
    <%activityBean.loadActivities();%>
    <form name = "updateactivity" action="activity_update2.jsp" method = "post">
        Activity to update:
        <select name="activityindex" id="activityindex">
            <%
                System.out.println("Number of Assets: " + activityBean.assetActivities.size());
                for (int i = 0; i < activityBean.assetActivities.size(); i++) {
                    AssetActivity a = new AssetActivity();
                    a = activityBean.assetActivities.get(i);
                    System.out.println(a.asset_id);%>

            <option value = "<%=i%>"><%=a.asset_id%> - <%=a.getAssetName()%> (<%=a.activity_date%>)</option>
            <% }%>
        </select>
        <br><br>
        <input type="submit" value="Update Asset" name="updateactivity" />
    </form>
</body>
</html>
