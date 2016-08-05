using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace parallelforeachtest
{
    class Program
    {
        static void Main(string[] args)
        {
            var values = Enumerable.Range(0, 16).Select(v => (int)Math.Pow(2, v));
            Console.WriteLine("For. /n");

            for (int i =0;i<values.Count();i++)
            {
                Console.WriteLine("{0}:\t{1}", i, values.ElementAt(i));

            }
            Console.WriteLine("Parallel ForEach. /n");
            Parallel.ForEach(values, (value, pls, index) =>
            {
                Console.WriteLine("{0}:\t{1}", index, value);
                //index++;
            });
            Console.WriteLine("Press a key to exit.");
            Console.ReadLine();
        }
    }
}
