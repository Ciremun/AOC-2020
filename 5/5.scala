import util.control.Breaks._
import scala.collection.mutable.ListBuffer

// What is the highest seat ID on a boarding pass?
// What is the ID of your seat?

object Main extends App
{
   def getSeatIDs(input: List[String]): ListBuffer[Int] = {
      var seatIDs = new ListBuffer[Int]()
      for (word <- input)
      {
        var row: ListBuffer[Int] = (0 to 127).to(ListBuffer)
        var column: ListBuffer[Int] = (0 to 7).to(ListBuffer)
        for (letter <- word)
        {
          if (letter == 'F')
            row = row.take(row.length / 2)
          else if (letter == 'B')
            row = row.drop(row.length / 2)
          else if (letter == 'L')
            column = column.take(column.length / 2)
          else if (letter == 'R')
            column = column.drop(column.length / 2)
        }
        seatIDs += row(0) * 8 + column(0)
      }
      return seatIDs
   }
  val source = io.Source.fromFile("input.txt")
  val input = source.getLines.filter(_.matches("[A-Za-z]+")).toList
  source.close()
  val seatIDs: ListBuffer[Int] = getSeatIDs(input)
  val sortedSeatIDs = seatIDs.sorted
  var previousID: Int = sortedSeatIDs(0)
  val possibleSeats = ListBuffer[Int]()
  println(s"pt.1 Highest Seat ID: ${seatIDs.max}")
  for (i <- sortedSeatIDs.drop(1))
  {
    if (i != previousID + 1)
    {
      possibleSeats += i - 1
      possibleSeats += i + 1
      previousID += 1
    }
    previousID += 1
  }
  println(s"pt.2 Your Seat ID: ${possibleSeats.mkString(" or ")}")
}