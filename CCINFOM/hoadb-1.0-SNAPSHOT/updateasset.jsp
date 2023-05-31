<%@ page import="com.example.hoadb.Asset" %>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="java.sql.*, java.util.*, hoadb.*" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Updated Asset</title>
</head>
<body>
<h1>Updated Asset</h1>
<jsp:useBean id="assetBean" class="com.example.hoadb.Asset" scope="session" />

<%
    assetBean.failed = false;
    assetBean.loadAssets();
    assetBean = assetBean.getAsset(Integer.parseInt(request.getParameter("index")));
    assetBean.for_rent = request.getParameter("yesOption") != null;
    assetBean.status = request.getParameter("status");
    assetBean.loc_latitude = Double.parseDouble(request.getParameter("curLocationX"));
    assetBean.loc_longitude = Double.parseDouble(request.getParameter("curLocationY"));
    String temp = request.getParameter("parentid");
    if (temp.equals("none")) {
        assetBean.enclosing_asset = -1;
    } else {
        assetBean.enclosing_asset = Integer.parseInt(temp);
    }
    assetBean.updateAsset();
    //Optional: add reset option



%>

<%
    if (!assetBean.failed){
%>
Listing contents of the cart so far<br>
Asset Name: <%=assetBean.asset_name%><br>
Asset Description: <%=assetBean.asset_description %><br>
Acquisition Date: <%=assetBean.acquisition_date%><br>
Rentable: <%=assetBean.for_rent%><br>
Asset Value: <%=assetBean.asset_value%><br>
Asset Type: <%=assetBean.typeString()%><br>
Asset Status: <%=assetBean.statusString()%><br>
Current Location: <%=assetBean.loc_latitude%> <%=assetBean.loc_longitude%><br>
HOA: <%=assetBean.hoa_name%><br>
Enclosing Asset: <%=assetBean.enclosing_asset%>
<%  } else { %>
<h3 style = "color: red">Asset Registration Failed.</h3>
Reason: <%=assetBean.errorMessage%> <br>
<%}%><br>
click <a href="index.jsp">here to go back to ordering</a><br>
</body>
</html>