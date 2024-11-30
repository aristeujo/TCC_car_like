#!/usr/bin/env python3
import rospy
import csv
from datetime import datetime
from my_project_msgs.msg import TasksGantt 

class TaskStateLogger:
    def __init__(self):
        # Arquivo para salvar os dados
        self.filename = "tasks_gantt.csv"

        # Cria o arquivo CSV e adiciona cabeçalho
        self.create_csv(self.filename, ["Task Index", "State", "Timestamp"])

        # Assina o tópico com os estados das tarefas
        rospy.Subscriber("/tasks_gantt", TasksGantt, self.tasks_callback)

    def create_csv(self, filename, header):
        """Cria um arquivo CSV com cabeçalhos."""
        with open(filename, 'w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(header)

    def tasks_callback(self, data):
        """Callback para o tópico /tasks_gantt."""
        rows = []

        for task in data.task_states:
            # Converte timestamp para um formato legível, se necessário
            timestamp = task.timestamp  # Ajuste conforme necessário
            rows.append([task.task_index, task.state, timestamp])

        # Escreve os dados no arquivo CSV
        self.write_to_csv(self.filename, rows)

    def write_to_csv(self, filename, rows):
        """Escreve múltiplas linhas no arquivo CSV especificado."""
        with open(filename, 'a', newline='') as file:
            writer = csv.writer(file)
            writer.writerows(rows)

if __name__ == "__main__":
    try:
        rospy.init_node("task_state_logger", anonymous=True)
        logger = TaskStateLogger()
        rospy.loginfo("Task state logger started. Writing to CSV file.")
        rospy.spin()
    except rospy.ROSInterruptException:
        rospy.loginfo("Task state logger stopped.")
