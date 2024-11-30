import csv
import matplotlib.pyplot as plt

# Configuração da duração mínima para barras
MIN_DURATION_MS = 10

# Tarefas que você deseja filtrar (por padrão, exibe todas)
TASK_FILTER = None  # Exemplo: TASK_FILTER = [0, 1]

# Função para ler o CSV e processar os dados
def read_csv(file_path):
    tasks = {}
    with open(file_path, 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            task_index = int(row["Task Index"])
            state = int(row["State"])
            timestamp = int(row["Timestamp"])

            if TASK_FILTER is None or task_index in TASK_FILTER:
                if task_index not in tasks:
                    tasks[task_index] = []
                tasks[task_index].append((timestamp, state))
    return tasks

# Função para processar os dados para o Gantt
def process_gantt_data(tasks):
    gantt_data = []
    for task_index, events in tasks.items():
        for i in range(len(events) - 1):
            start_time, state = events[i]
            end_time, next_state = events[i + 1]

            # Apenas considerar transições de ativo (state=1) para inativo (state=0)
            if state == 1 and next_state == 0:
                duration = max(end_time - start_time, MIN_DURATION_MS)  # Garantir duração mínima
                gantt_data.append((f"Tarefa {task_index}", start_time, duration))
    return gantt_data

# Função para plotar o gráfico de Gantt
def plot_gantt(gantt_data):
    if gantt_data:
        fig, ax = plt.subplots(figsize=(12, 6))
        for task_name, start_time, duration in gantt_data:
            ax.barh(task_name, duration, left=start_time, height=0.4, color="blue")

        # Configurações do gráfico
        ax.set_xlabel("Tempo (milissegundos)")
        ax.set_ylabel("Tarefas")
        ax.set_title("Gráfico de Gantt - Execução de Tarefas")
        ax.grid(axis="x", linestyle="--", alpha=0.7)

        # Exibir o gráfico
        plt.show()
    else:
        print("Nenhum dado válido para exibir no gráfico de Gantt.")

# Caminho do arquivo CSV
file_path = "tasks_gantt.csv"

# Executar o fluxo
tasks = read_csv(file_path)  # Lê o CSV e organiza os dados por tarefa
gantt_data = process_gantt_data(tasks)  # Processa os dados para o gráfico

# Debug: Mostrar os dados processados
print("Dados de Gantt Processados:")
for entry in gantt_data:
    print(f"Tarefa: {entry[0]}, Início: {entry[1]}, Duração: {entry[2]} ms")

# Plotar o gráfico
plot_gantt(gantt_data)
