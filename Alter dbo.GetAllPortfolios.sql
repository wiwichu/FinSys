USE [FinSys.EFData.FinSysContext]
GO

/****** Object: SqlProcedure [dbo].[GetAllPortfolios] Script Date: 11/14/2015 11:52:47 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

ALTER PROCEDURE GetAllPortfolios
					AS
					SELECT * FROM Portfolios
