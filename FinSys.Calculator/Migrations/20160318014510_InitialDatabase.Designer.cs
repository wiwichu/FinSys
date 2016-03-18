using System;
using Microsoft.Data.Entity;
using Microsoft.Data.Entity.Infrastructure;
using Microsoft.Data.Entity.Metadata;
using Microsoft.Data.Entity.Migrations;
using FinSys.Calculator.Models;

namespace FinSys.Calculator.Migrations
{
    [DbContext(typeof(FinSysContext))]
    [Migration("20160318014510_InitialDatabase")]
    partial class InitialDatabase
    {
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
            modelBuilder
                .HasAnnotation("ProductVersion", "7.0.0-rc1-16348")
                .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

            modelBuilder.Entity("FinSys.Calculator.Models.Log", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<DateTime>("LogTime");

                    b.Property<string>("Message");

                    b.Property<string>("Severity");

                    b.Property<string>("Topic");

                    b.Property<string>("User");

                    b.HasKey("Id");
                });
        }
    }
}
