namespace FinSis.EFData.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class PositionsKey : DbMigration
    {
        public override void Up()
        {
            DropForeignKey("dbo.Positions", "PortfolioId", "dbo.Portfolios");
            DropIndex("dbo.Positions", new[] { "PortfolioId" });
            DropPrimaryKey("dbo.Positions");
            AlterColumn("dbo.Positions", "PortfolioId", c => c.String(nullable: false, maxLength: 128));
            AlterColumn("dbo.Positions", "InstrumentId", c => c.String(nullable: false, maxLength: 128));
            AddPrimaryKey("dbo.Positions", new[] { "PortfolioId", "InstrumentId" });
            CreateIndex("dbo.Positions", "PortfolioId");
            AddForeignKey("dbo.Positions", "PortfolioId", "dbo.Portfolios", "Id", cascadeDelete: true);
            DropColumn("dbo.Positions", "Id");
        }
        
        public override void Down()
        {
            AddColumn("dbo.Positions", "Id", c => c.Int(nullable: false, identity: true));
            DropForeignKey("dbo.Positions", "PortfolioId", "dbo.Portfolios");
            DropIndex("dbo.Positions", new[] { "PortfolioId" });
            DropPrimaryKey("dbo.Positions");
            AlterColumn("dbo.Positions", "InstrumentId", c => c.String());
            AlterColumn("dbo.Positions", "PortfolioId", c => c.String(maxLength: 128));
            AddPrimaryKey("dbo.Positions", "Id");
            CreateIndex("dbo.Positions", "PortfolioId");
            AddForeignKey("dbo.Positions", "PortfolioId", "dbo.Portfolios", "Id");
        }
    }
}
