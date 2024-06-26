#include <iostream>
#include <string>
#include <fstream> // biblioteca utilizada para operações de entrada e saída de arquivos

using namespace std;

#define MAX_ALUNOS 999
#define MAX_TURMA 40
#define NUM_DISCIPLINAS 2
#define NUM_MATERIAS 2

//Deixei definido as turmas, alunos, diciplina e materia

class Aluno {
public:
    string nome;
    string disciplinas[NUM_MATERIAS][NUM_DISCIPLINAS];
    float notas[NUM_MATERIAS][NUM_DISCIPLINAS];

    Aluno() {
        nome = "";
        for (int i = 0; i < NUM_MATERIAS; ++i) {
            for (int j = 0; j < NUM_DISCIPLINAS; ++j) {
                disciplinas[i][j] = "";
                notas[i][j] = 0.0;
            }
        }
    }
    //funcoes criadas

    void adicionarDisciplinaENota(int materia, int disciplina, string nomeDisciplina, float nota) {
        if (materia >= 0 && materia < NUM_MATERIAS && disciplina >= 0 && disciplina < NUM_DISCIPLINAS) {
            disciplinas[materia][disciplina] = nomeDisciplina;
            notas[materia][disciplina] = nota;
        } else {
            cout << "Erro: Indice de materia ou disciplina invalido." << endl;
        }
    }

    void exibirNotas() {
        cout << "Notas de " << nome << ":" << endl;
        for (int i = 0; i < NUM_MATERIAS; ++i) {
            cout << "Materia " << i + 1 << ":" << endl;
            float somaNotas = 0.0;
            for (int j = 0; j < NUM_DISCIPLINAS; ++j) {
                cout << "  " << disciplinas[i][j] << ": " << notas[i][j] << endl;
                somaNotas += notas[i][j];
            }
            float media = somaNotas / NUM_DISCIPLINAS;
            cout << "  Media: " << media << endl;
        }
    }

    void exibirAluno() {
        cout << "Aluno: " << nome << endl;
        exibirNotas();
    }
};

class Turma {
public:
    Aluno alunos[MAX_TURMA];
    int num_alunos;

    Turma() {
        num_alunos = 0;
    }

    void adicionarAluno(Aluno aluno) {
        if (num_alunos < MAX_TURMA) {
            alunos[num_alunos++] = aluno;
        } else {
            cout << "Erro: Numero maximo de alunos na turma atingido." << endl;
        }
    }

    void exibirTurma() {
        if (num_alunos == 0) {
            cout << "Nenhum aluno na turma." << endl;
        } else {
            for (int i = 0; i < num_alunos; i++) {
                alunos[i].exibirAluno();
            }
        }
    }

    Aluno* buscarAluno(string nome) {
        for (int i = 0; i < num_alunos; i++) {
            if (alunos[i].nome == nome) {
                return &alunos[i];
            }
        }
        return nullptr;
    }

    void salvarTurma(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Erro ao abrir o arquivo para escrita." << endl;
            return;
        }

        file << num_alunos << endl;
        for (int i = 0; i < num_alunos; ++i) {
            file << alunos[i].nome << endl;
            for (int j = 0; j < NUM_MATERIAS; ++j) {
                for (int k = 0; k < NUM_DISCIPLINAS; ++k) {
                    file << alunos[i].disciplinas[j][k] << " " << alunos[i].notas[j][k] << endl;
                }
            }
        }

        file.close();
        cout << "Turma salva com sucesso." << endl;
    }

    void carregarTurma(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Erro ao abrir o arquivo para leitura." << endl;
            return;
        }

        file >> num_alunos;
        file.ignore();  // Ignora o caractere de nova linha após o número de alunos
        for (int i = 0; i < num_alunos; ++i) {
            getline(file, alunos[i].nome);
            for (int j = 0; j < NUM_MATERIAS; ++j) {
                for (int k = 0; k < NUM_DISCIPLINAS; ++k) {
                    file >> alunos[i].disciplinas[j][k] >> alunos[i].notas[j][k];
                }
            }
            file.ignore();  // Ignorar o caractere de nova linha após cada aluno
        }

        file.close();
        cout << "Turma carregada com sucesso." << endl;
    }
};

int main() {
    Turma turma;
    int opcao;
    const string filename = "turma.txt";

    // Carregar turma do arquivo ao iniciar o programa
    turma.carregarTurma(filename);

    do {
        cout << "1. Adicionar aluno" << endl;
        cout << "2. Adicionar nota e disciplina para aluno" << endl;
        cout << "3. Exibir notas de aluno" << endl;
        cout << "4. Exibir todos os alunos da turma" << endl;
        cout << "5. Salvar turma" << endl;
        cout << "6. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (opcao == 1) {
            if (turma.num_alunos < MAX_TURMA) {
                Aluno novo_aluno;
                cout << "Digite o nome do aluno: ";
                cin >> novo_aluno.nome;
                turma.adicionarAluno(novo_aluno);
            } else {
                cout << "Erro: Numero maximo de alunos na turma atingido." << endl;
            }
        } else if (opcao == 2) {
            string nome;
            cout << "Digite o nome do aluno: ";
            cin >> nome;
            Aluno* aluno = turma.buscarAluno(nome);
            if (aluno != nullptr) {
                for (int m = 0; m < NUM_MATERIAS; ++m) {
                    for (int d = 0; d < NUM_DISCIPLINAS; ++d) {
                        string disciplina;
                        float nota;
                        cout << "Digite o nome da disciplina " << d +1  << " da materia " << m +1 << ": ";
                        cin >> disciplina;
                        cout << "Digite a nota para " << disciplina << ": ";
                        cin >> nota;
                        aluno->adicionarDisciplinaENota(m, d, disciplina, nota);
                    }
                }
            } else {
               cout << "Aluno nao encontrado!" << endl;
            }
        } else if (opcao == 3) {
            string nome;
            cout << "Digite o nome do aluno: ";
            cin >> nome;
            Aluno* aluno = turma.buscarAluno(nome);
            if (aluno != nullptr) {
                aluno->exibirNotas();
            } else {
                cout << "Aluno nao encontrado!" << endl;
            }
        } else if (opcao == 4) {
            turma.exibirTurma();
        } else if (opcao == 5) {
            turma.salvarTurma(filename);
        } else if (opcao != 6) {
            cout << "Opcao invalida! Tente novamente." << endl;
        }
    } while (opcao != 6);

    // Salvar turma no arquivo ao sair do programa
    turma.salvarTurma(filename);

    return 0;
}