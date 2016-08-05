using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using FinSysCore.Models;

namespace FinSysCore.Migrations
{
    [DbContext(typeof(FinSysContext))]
    [Migration("20160726000456_InitialDatabase")]
    partial class InitialDatabase
    {
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
            modelBuilder
                .HasAnnotation("ProductVersion", "1.0.0-rtm-21431")
                .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

            modelBuilder.Entity("FinSysCore.Models.Log", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<DateTime>("LogTime");

                    b.Property<string>("Message");

                    b.Property<string>("Severity");

                    b.Property<string>("Topic");

                    b.Property<string>("User");

                    b.HasKey("Id");

                    b.ToTable("Logs");
                });
        }
    }
}
