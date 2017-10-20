from __future__ import print_function
import numpy as np
import json
import matplotlib.pyplot as plt
from matplotlib import cm
import matplotlib.colors as colors
import sys

def two_well(x,y):
    return x**4 - x**2 + y**2

def one_well(x,y):
    return x**2 + y**2

def asymmetric_one_well(x, y, x_curv=1.0, y_curv=0.10):
    return x_curv*x**2 + y_curv*y**2

def plot_positions(positions, potfunc, outpng, U_mat = None, weights = None):
    fig = plt.figure()
    ax = fig.add_subplot(111)

    #plot the trajectory
    cmap = cm.coolwarm
    cmap_norm = colors.Normalize(vmin=0,vmax=positions.shape[0])
    scalar_map = cm.ScalarMappable(norm=cmap_norm,cmap=cmap)
    for step in range(positions.shape[0]):
        ax.scatter(positions[step,0],positions[step,1],c=scalar_map.to_rgba(step),zorder=3)
    ax.plot(positions[:,0],positions[:,1],'k-',zorder=2,linewidth=0.4)

    #plot any eigenvectors, if asked for
    if U_mat is not None:
        for col_idx in range(U_mat.shape[1]):
            #select out the eigenvector we want
            vector = U_mat[:,col_idx]
            xlim = ax.get_xlim()
            ylim = ax.get_ylim()
            fig_corner_norm = np.linalg.norm(np.array(xlim[-1], ylim[-1]))

            if weights is not None:
                scale_factor = np.sqrt(0.1*fig_corner_norm)*weights[col_idx]
            else:
                scale_factor = np.sqrt(0.1*fig_corner_norm)

            vector *= scale_factor
            print(vector)
            ax.arrow(0, 0, vector[0], vector[1], zorder=3)

    #also plot the doublewell potential
    xlim = ax.get_xlim()
    ylim = ax.get_ylim()
    grid_x,grid_y = np.meshgrid(np.linspace(xlim[0],xlim[1],100),np.linspace(ylim[0],ylim[1],100))
    pot = potfunc(grid_x,grid_y)
    ax_contour = ax.contour(grid_x,grid_y,pot,100,zorder=1)
    fig.colorbar(ax_contour)

    #cosmetics
    plt.xlabel('x')
    plt.ylabel('y')
    plt.axis('equal')
    plt.savefig(outpng)

def stride_positions(positions, stride):
    return positions[::stride, :]

def do_plot(args):
    potfunc = asymmetric_one_well

    traj_path, stride, outpng = args
    stride = int(stride)

    positions = np.loadtxt(traj_path,delimiter=' ')
    positions = stride_positions(positions, stride)

    plot_positions(positions, potfunc, outpng)

def diagonalize(M):
    #diagonalize M into U . D . U^T
    d, u = np.linalg.eigh(M)

    #sort them in order of descending eigenvalues
    permutation = np.argsort(d)[::-1]
    D = np.diag(d[permutation])
    U = u[permutation]

    #sanity check that U . D . U^T indeed reconstructs M
    M_r = (U.T).dot(D).dot(U)
    assert np.allclose(M, M_r), 'UDU^T does not reconstruct M!'

    return U, D

def do_pca(args):
    #load up the trajectory
    traj_path, stride, outpng = args
    stride = int(stride)
    positions = np.loadtxt(traj_path,delimiter=' ')
    positions = stride_positions(positions, stride)

    #compute the _scaled_ data matrix C
    C = positions
    num_samples = C.shape[0]
    C /= np.sqrt(num_samples)

    #compute the scaled covariance matrix (1/N) C^T C
    sigma = C.T.dot(C)

    #diagonalize
    U, D = diagonalize(sigma)

    #weights when plotted should be ratio of eigenvalues
    weights = np.diag(D)/np.sum(np.diag(D))

    potfunc = asymmetric_one_well
    plot_positions(positions, potfunc, outpng, U_mat=U, weights=weights)

def dispatcher(sargs):
    dispatch_module = sargs[0]
    module_args = sargs[1:]

    AV_MODULES = ['plot', 'pca']

    assert dispatch_module in AV_MODULES 

    if dispatch_module == 'plot':
        do_plot(module_args)
    elif dispatch_module == 'pca':
        do_pca(module_args)

if __name__ == "__main__":
    dispatcher(sys.argv[1:])