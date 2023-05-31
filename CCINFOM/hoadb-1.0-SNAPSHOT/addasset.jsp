<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="java.sql.*, java.util.*, hoadb.*" %>
<html>
<head>
    <link rel="stylesheet" href="style.css">
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Add Asset Processing</title>
</head>
<body>
<h1>Adding Asset to Database</h1>
<jsp:useBean id="assetBean" class="com.example.hoadb.Asset" scope="session" />

<%
    assetBean.failed = false;
    assetBean.loadAssets();
    int max_id = assetBean.assets.get(assetBean.assets.size() - 1).asset_id;
    assetBean.asset_id = max_id + 1;
    //int id = Integer.parseInt(request.getParameter("asset id"));
    assetBean.asset_name = request.getParameter("name");
    assetBean.asset_description  = request.getParameter("desc");
    assetBean.acquisition_date = request.getParameter("acqdate");
    assetBean.for_rent = request.getParameter("yesOption") != null;
    assetBean.asset_value = Float.parseFloat(request.getParameter("assetvalue"));
    assetBean.type_asset = request.getParameter("types");
    assetBean.status = request.getParameter("status");
    assetBean.hoa_name = request.getParameter("HOA");
    assetBean.loc_latitude = Double.parseDouble(request.getParameter("curLocationX"));
    assetBean.loc_longitude = Double.parseDouble(request.getParameter("curLocationY"));
    String temp = request.getParameter("parentid");
    if (temp.equals("none")) {
        assetBean.enclosing_asset = -1;
    } else {
        assetBean.enclosing_asset = Integer.parseInt(temp);
    }
    //Optional: add reset option
    assetBean.addRecord();

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
    Asset Type: <%=assetBean.type_asset%><br>
    Asset Status: <%=assetBean.status%><br>
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
