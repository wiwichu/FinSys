using System;
using FinSysCore.Models;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;

namespace FinSysCore.Migrations
{
    [DbContext(typeof(FinSysContext))]
    partial class FinSysContextModelSnapshot : ModelSnapshot
    {
        protected override void BuildModel(ModelBuilder modelBuilder)
        {
            modelBuilder
                .HasAnnotation("ProductVersion", "7.0.0-rc1-16348")
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
                });
        }
    }
}
