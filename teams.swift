import Foundation

func calculatePoints(forMatches results: [String]) -> [String: Int] {
    var teamPoints = [String: Int]()

    for result in results {
        let components = result.components(separatedBy: ":")
        
        // Проверка на корректность формата результата матча
        guard components.count == 2, let homeScore = Int(components[0]), let awayScore = Int(components[1]) else {
            print("Ошибка в формате результата матча: \(result)")
            continue
        }

        // Определение команд и распределение очков
        if homeScore > awayScore {
            teamPoints["Команда №1", default: 0] += 3
            teamPoints["Команда №2", default: 0] += 0
        } else if homeScore < awayScore {
            teamPoints["Команда №1", default: 0] += 0
            teamPoints["Команда №2", default: 0] += 3
        } else {
            teamPoints["Команда №1", default: 0] += 1
            teamPoints["Команда №2", default: 0] += 1
        }
    }

    return teamPoints
}

// Ввод результатов матчей с консоли
print("Введите результаты матчей через пробел:")
print("Пример: 3:3 0:0 2:0")
if let input = readLine() {
    let matchResults = input.components(separatedBy: " ")
    let teamPoints = calculatePoints(forMatches: matchResults)

    for (team, points) in teamPoints {
        print("\(team) набрала \(points) очков")
    }
} else {
    print("Ошибка при чтении ввода")
}
