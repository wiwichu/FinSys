namespace FinSis.EFData.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class Initial : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Portfolios",
                c => new
                    {
                        Id = c.String(nullable: false, maxLength: 128),
                    })
                .PrimaryKey(t => t.Id);
            
            CreateTable(
                "dbo.Positions",
                c => new
                    {
                        Id = c.Int(nullable: false, identity: true),
                        PortfolioId = c.String(maxLength: 128),
                        InstrumentId = c.String(),
                        Amount = c.Double(nullable: false),
                        Price = c.Double(nullable: false),
                    })
                .PrimaryKey(t => t.Id)
                .ForeignKey("dbo.Portfolios", t => t.PortfolioId)
                .Index(t => t.PortfolioId);
            
            CreateTable(
                "dbo.Trades",
                c => new
                    {
                        Id = c.Int(nullable: false, identity: true),
                        PortfolioId = c.String(maxLength: 128),
                        InstrumentId = c.String(),
                        Amount = c.Double(nullable: false),
                        Price = c.Double(nullable: false),
                        ValueDate = c.DateTime(nullable: false),
                        CounterParty = c.String(),
                    })
                .PrimaryKey(t => t.Id)
                .ForeignKey("dbo.Portfolios", t => t.PortfolioId)
                .Index(t => t.PortfolioId);
            
        }
        
        public override void Down()
        {
            DropForeignKey("dbo.Trades", "PortfolioId", "dbo.Portfolios");
            DropForeignKey("dbo.Positions", "PortfolioId", "dbo.Portfolios");
            DropIndex("dbo.Trades", new[] { "PortfolioId" });
            DropIndex("dbo.Positions", new[] { "PortfolioId" });
            DropTable("dbo.Trades");
            DropTable("dbo.Positions");
            DropTable("dbo.Portfolios");
        }
    }
}
