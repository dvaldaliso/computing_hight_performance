% Test the function with the given matrix A and initial values
A = [4, 1, 2, 1, 0;
     1, 3, 0, 1, 1;
     2, 0, 2, 2, 1;
     1, 1, 2, 3, 2;
     0, 1, 1, 2, 2];

x0 = ones(5, 1);
lambda0 = 1.0;

[x, lambda] = newton_rap(A, x0, lambda0);


disp('True eigenvalues:');
disp(eig(A));
disp('Found eigenvalue:');
disp(lambda);
disp('Found eigenvector:');
disp(x);