using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LinqTests
{
    internal class Person
    {
        public string Name { get; set; }
        public int Age { get; set; }
        public Person ShallowCopy()
        {
            return (Person)this.MemberwiseClone();
        }
    }
    class Program
    {
        
        static void Main(string[] args)
        {
            var input = "10,5,0,8,10,1,4,0,10,1".Split(',');
            //Sum all except lowest 3.
            var result1 = input.Select(c => Convert.ToInt16(c)).OrderBy(c=> c).Skip(3).Sum(c=> c);
            Console.WriteLine(result1);

            Console.WriteLine(input.Count(c => Convert.ToInt16(c) > 5));

            var ports = new[]
            {
                new {port= "A",instr= 1},
                new {port= "A",instr= 2},
                new {port= "A",instr= 3},
                new {port= "B",instr= 1},
                new {port= "C",instr= 1},
                new {port= "C",instr= 3},
                new {port= "D",instr= 4},
                new {port= "D",instr= 1},
                new {port= "D",instr= 5}
            };

            var result2 = ports.GroupBy(p => p.port)
                .ToDictionary(p => p.Key, p => p.ToList());

            var input2 = "2,5,7-10,11,17-18".Split(',');
            var result3 = input2
                .Select(c=> !c.Contains("-") ? new List<int>() { int.Parse(c)} :
                Enumerable.Range(int.Parse(c.Split('-')[0]), int.Parse(c.Split('-')[1])+1 - int.Parse(c.Split('-')[0])).ToList()
                )
                .SelectMany(c=>c)
                ;
            Console.WriteLine("input2");
            foreach (string s in input2)
            {
                Console.WriteLine(s);
            }
            Console.WriteLine("result3:");
            foreach (int i in result3)
            {
                Console.WriteLine(i);
            }


            var pets = "Dog,Cat,Rabbit,Dog,Dog,Lizard,Cat,Cat,Dog,Rabbit,Guinea Pig,Dog".Split(',');
            //var result4 = pets.GroupBy(c => c, e => e == "Dog" || e == "Cat" ? e : "Other").Select(g=> new { name = g.Key, total = g.Count() }) ;
            var result4 = pets.GroupBy(e => e == "Dog" || e == "Cat" ? e : "Other")
                .Select(g => new { name = g.Key, total = g.Count() });

            for (int i = 0; i < result4.Count();++i)
            {
                Console.WriteLine($"Name: {result4.ElementAt(i).name} Total: {result4.ElementAt(i).total}" );
            }


            Person personA = new Person();
            personA.Name = "Me";
            personA.Age = 20;
            Person personB = personA;
            personA.Age = 50;

            Console.WriteLine($"Reference Test1");
            Console.WriteLine($"NameB: {personB.Name} AgeB: {personB.Age}");
            Console.WriteLine($"NameA: {personA.Name} AgeA: {personA.Age}");

            personB = personA.ShallowCopy();
            personA.Age = 40;

            Console.WriteLine($"Reference Test2");
            Console.WriteLine($"NameB: {personB.Name} AgeB: {personB.Age}");
            Console.WriteLine($"NameA: {personA.Name} AgeA: {personA.Age}");

            Console.ReadLine();
        }
    }
}
